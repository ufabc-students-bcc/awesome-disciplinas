/*jshint esversion: 6 */

(function() {
  "use strict";

  let Transform = require('stream').Transform;


  let fs = require('fs'),
      tmp = require('tmp'),
      path = require('path'),
      spawn = require('child_process').spawn,
      vinyl = require('vinyl-file'),
      lazypipe = require('lazypipe'),
      gulp = require('gulp'),
      gutil = require('gulp-util'),
      slash = require('slash');


  let spawnlog = function(tool) {
    return function(data) {
      for (let line of data.toString().split('\n')) {
        gutil.log(tool + ':', line);
      }
    };
  };


  let tracer = function(tool, override) {
    return function(...message) {
      if (override || (override === undefined && compile.trace)) {
        gutil.log(tool + ':', ...message);
      }
    };
  };

  // 2016-12-19: Used to correct paths on Windows machines
  let fixPath = function(path) {
    if (process.platform === 'win32') return slash(path);
    return path;
  };


  var javac = function({
      debuggingInformation = ['lines', 'source'],
      javaVersion,
      failOnWarning = false,
      noWarnings = false,
      javacToolPath = 'javac',
      verbose = false,
      traceEnabled,
      javacCompilerFlags = []} = {}) {

    let trace = tracer('javac', traceEnabled);

    // List of all the promises that need to be fulfilled before we can run.
    let pendingWork = [];

    // List of libraries referenced.
    let libraries = [];

    let sources = [];

    // Main transform stream for reading source files and writing class files.
    let compileStream = new Transform({
        readableObjectMode: true,
        writableObjectMode: true,
        transform(file, enc, next) {
          if (!file.isDirectory()) {
            trace('Source file:', fixPath(file.path));
            sources.push(fixPath(file.path));
            next();
          }
        },
        flush(next) {
          Promise.all(pendingWork)
            .then(function() {
              // javac option file for source files.
              let sourceFile = tmp.fileSync(),
                  sourceFileStream = fs.createWriteStream(null, {fd: sourceFile.fd});

              for (let source of sources) {
                sourceFileStream.write(`"${source}"\n`);
              }

              sourceFileStream.end();
              trace('Source File Path:', fixPath(sourceFile.name));

              // javac option file for other arguments.
              let argFile = tmp.fileSync(),
                  argFileStream = fs.createWriteStream(null, {fd: argFile.fd});

              // Output folder for .class files.
              let outputFolder = fixPath(tmp.dirSync({unsafeCleanup: true}).name);
              argFileStream.write(`-d "${outputFolder}"\n`);

              for (let flag of javacCompilerFlags) {
                argFileStream.write(`-J${flag}\n`);
              }

              if (typeof debuggingInformation != "string") {
                debuggingInformation = (debuggingInformation || []).join(',') || 'none';
              }
              if (debuggingInformation == "*") {
                argFileStream.write(`-g\n`);
              } else {
                argFileStream.write(`-g:${debuggingInformation}\n`);
              }

              if (verbose) argFileStream.write('-verbose\n');
              if (noWarnings) argFileStream.write('-nowarn\n');
              if (failOnWarning) argFileStream.write('-Werror\n');

              if (javaVersion) {
                argFileStream.write(`-source ${javaVersion}\n`);
                argFileStream.write(`-target ${javaVersion}\n`);
              }

              if (libraries.length > 0) {
                argFileStream.write(
                    `-classpath "${libraries.join(path.delimiter)}"\n`);
              }

              argFileStream.end();
              trace('Argument File Path:', fixPath(argFile.name));

              // And here... we... go...
              trace('javac', 'Executing:', javacToolPath);
              let javacProc = spawn(javacToolPath, [
                  '@' + fixPath(argFile.name),
                  '@' + fixPath(sourceFile.name)]);

              javacProc.stdout.on('data', spawnlog('javac'));
              javacProc.stderr.on('data', spawnlog('javac'));

              javacProc.on('close', function(code) {
                trace('javac', 'javac complete; code:', code);
                if (code !== 0) {
                  throw new gutil.PluginError('gulp-javac', 'javac failed');
                } else {
                  gulp.src(path.join(outputFolder, '**'), {nodir: true})
                    .on('data', function(chunk) { compileStream.push(chunk); })
                    .on('end', next);
                }
              });
            })
            .catch(function(error) {
              gutil.log(error);
              throw new gutil.PluginError('gulp-javac', 'javac failed');
            });
        }});

    /** Adds a library path. Accepts string, string[], or source stream. */
    compileStream.addLibraries = function(...sources) {
      const libraryAdder = function(file) {
          if (!file.isDirectory()) {
            trace('Library added:', fixPath(file.path));
            libraries.push(fixPath(file.path));
          }
        };

      for (let source of sources) {
        let stream;
        if (typeof source == "string" || Array.isArray(source)) {
          // Make string-y things into source stream.
          trace('Adding libraries from path(s):', source);
          stream = gulp.src(source);
        } else {
          // Assume anything else is stream-y.
          trace('Adding libraries from stream:', typeof source);
          stream = source;
        }

        // Pipe all libraries directly to the option stream.
        stream.on('data', libraryAdder);

        // Add waiting for all libraries to the promises.
        pendingWork.push(new Promise(function(fulfill, reject) {  // jshint ignore:line
          stream.on('end', function() {
            trace('javac', 'Library stream complete');
            fulfill();
          });
        }));
      }

      return compileStream;
    };

    trace('Created javac task');

    return compileStream;
  };


  var jar = function(jarName, {
      omitManifest = false,
      entrypoint,
      jarToolPath = 'jar',
      verbose = false,
      traceEnabled,
      jarCompilerFlags = []} = {}) {

    let trace = tracer('jar', traceEnabled);

    let jarPath, jarFolder;
    let jarList = [];

    let jarBatch = function(next) {
        if (jarList.length === 0) {
          next();
          return;
        }

        let args = [];
        let options = ['u', 'f'];
        if (!jarPath) {
          jarFolder = fixPath(tmp.dirSync({unsafeCleanup: false}).name);
          jarPath = path.join(jarFolder, jarName);

          try {
            fs.mkdirSync(path.dirname(jarPath));
          } catch (e) {
            // Meh. Probably exists.
            if (e.code !== 'EEXIST') throw e;
          }

          trace('Creating jar:', jarPath);

          options = ['c', 'f'];
          if (entrypoint) {
            options.push('e');
            args.push(entrypoint);
          }
        }

        if (verbose) options.push('v');
        if (omitManifest) options.push('M');

        for (let file of jarList) {
          args.push('-C', file.base, file.relative);
        }

        args.unshift(jarPath);
        args.unshift(options.join(''));

        // And here... we... go...
        trace('Executing:', jarToolPath, args);

        let jarProc = spawn(jarToolPath, args);

        jarProc.stdout.on('data', spawnlog('jar'));
        jarProc.stderr.on('data', spawnlog('jar'));

        jarProc.on('close', function(code) {
          trace('jar complete; code:', code);
          if (code !== 0) {
            jarStream.emit('jar failed');
            jarStream.push(null);
          }
          next();
        });
      };

    let jarStream = new Transform({
        readableObjectMode: true,
        writableObjectMode: true,
        transform(file, enc, next) {
          jarList.push(file);
          if (jarList.length >= 40) {
            jarBatch(next);
            jarList = [];
          } else {
            next();
          }
        },
        flush(next) {
          jarBatch(function() {
              vinyl.read(jarPath, { base: jarFolder })
                .then(function(file) {
                    jarStream.push(file);
                    jarStream.push(null);
                    next();
                  });
            });
        }});

    trace('Created jar task');

    return jarStream;
  };


  var unjar = function({
      jarToolPath = 'jar',
      includeAllFiles = false,
      verbose = false,
      traceEnabled} = {}) {

    let trace = tracer('unjar', traceEnabled);

    let unjarStream = new Transform({
        readableObjectMode: true,
        writableObjectMode: true,
        transform(file, enc, next) {
          let outputFolder = fixPath(tmp.dirSync({unsafeCleanup: true}).name);

          trace('Expanding jar into', outputFolder);

          let args = ['-xf' + verbose ? 'v' : '', fixPath(file.path)];

          // And here... we... go...
          trace('Executing:', jarToolPath, args);
          let unjarProc = spawn(jarToolPath, args, {'cwd': outputFolder});

          unjarProc.stdout.on('data', spawnlog('unjar'));
          unjarProc.stderr.on('data', spawnlog('unjar'));

          unjarProc.on('close', function(code) {
            trace('unjar complete; code:', code);
            if (code !== 0) {
              throw new gutil.PluginError('gulp-unjar', 'unjar failed');
            } else {
              let spec = path.join('**', includeAllFiles ? '*' : '*.class');
              gulp.src(path.join(outputFolder, spec), {nodir: true})
                .on('data', function(chunk) { unjarStream.push(chunk); })
                .on('end', next);
            }
          });
        },
        flush(next) {
          next();
        }});

    trace('Created unjar task');

    return unjarStream;
  };



  var compile = function(jarName, options) {
    let javacInstance;

    let javacBuilder = function(...args) {
        javacInstance = javac(...args);
        return javacInstance;
      };

    let result = lazypipe()
      .pipe(javacBuilder, options)
      .pipe(jar, jarName, options)();

    result.addLibraries = function(...args) {
        javacInstance.addLibraries(...args);
        return result;
      };

    return result;
  };

  module.exports = compile;
  module.exports.compile = compile;
  module.exports.javac = javac;
  module.exports.jar = jar;
  module.exports.unjar = unjar;
  module.exports.trace = process.argv.indexOf('--gulp-javac.trace') >= 0;
})();

