/*jshint esversion: 6 */

(function() {
  "use strict";

  let gulp = require('gulp'),
      jshint = require('gulp-jshint'),
      spawn = require('child_process').spawn;

  gulp.task('lint', function() {
    return gulp.src(['**/*.js', '**/*.json', '!node_modules/**'])
      .pipe(jshint())
      .pipe(jshint.reporter('default'));
  });

  gulp.task('default', ['lint', 'run-tests']);

  let testProcess;

  gulp.task('run-tests', function() {
    if (testProcess) testProcess.kill();
    testProcess = spawn(
        'gulp',
        ['--gulpfile', 'test/gulpfile.js', '--gulp-javac.trace'],
        {stdio: 'inherit'});
  });

  gulp.task('continuous', function() {
    gulp.watch('*.js', ['lint']);
    gulp.watch(['*.js', 'test/**/*', '!test/out/**/*'], ['run-tests']);
  });
})();

