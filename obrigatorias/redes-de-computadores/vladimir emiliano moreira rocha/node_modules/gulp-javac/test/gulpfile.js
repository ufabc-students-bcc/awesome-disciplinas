/*jshint esversion: 6 */

(function() {
  "use strict";

  const del = require('del'),
        gulp = require('gulp'),
        javac = require('../javac'),
        merge = require('merge-stream'),
        unzip = require('gulp-unzip'),
        minimatch = require('minimatch'),
        intermediate = require('gulp-intermediate');

  gulp.task('clean', function() {
      del.sync('out');
    });

  gulp.task('simple-manual', ['clean'], function() {
      return gulp.src('simple/**/*')
        .pipe(javac.javac())
        .pipe(javac.jar('simple-manual.jar', {entrypoint: "test_package.TestClass"}))
        .pipe(gulp.dest('out/'));
    });

  gulp.task('simple-combined', ['clean'], function() {
      return gulp.src('simple/**/*')
        .pipe(javac('deep/simple-combined.jar', {entrypoint: "test_package.TestClass"}))
        .pipe(gulp.dest('out/'));
    });

  gulp.task('partial', ['clean', 'simple-manual'], function() {
      return gulp.src('dependent/**/*')
        .pipe(javac('partial.jar', {entrypoint: "dependent_package.DependentClass"})
            .addLibraries('out/simple-manual.jar'))
        .pipe(gulp.dest('out/'));
    });


  gulp.task('repackaging', ['clean', 'simple-manual'], function() {
      return merge(
          gulp.src('dependent/**/*')
            .pipe(javac.javac()
                .addLibraries('out/simple-manual.jar')),
          gulp.src('out/simple-manual.jar')
            .pipe(javac.unjar()))
        .pipe(javac.jar('repackaged.jar', {entrypoint: "dependent_package.DependentClass"}))
        .pipe(gulp.dest('out/repackaged/'));
    });
        

  gulp.task('default', ['simple-manual', 'simple-combined', 'partial', 'repackaging']);
})();

