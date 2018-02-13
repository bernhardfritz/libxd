<p align="center">
  <a href="https://bernhardfritz.github.io/libxd/">
    <img alt="libxd" src="./docs/_media/logo.svg">
  </a>
</p>

<p align="center">
  A simple 2D graphics library for C++.
</p>

# Links

* [Documentation](https://bernhardfritz.github.io/libxd/)

# Changelog

## 0.0.2

### Added
* the possibility to define mouse event callbacks using the functions `mouseMoved()`, `mousePressed()`, `mouseReleased()`, `mouseWheel()`.
* mouse example.
* Google Analytics.

### Changed
* the documentation.

### Fixed
* the lib folder being wrongly identified as a first party source folder by github's linguist.

## 0.0.1

This is the start of libxd as a remote repository. Prior to publishing libxd to github goes about 2 months of local development. These are rudimentary changelogs from the time before github:

### Added

* the functions `setup()`, `draw()` and `destroy()` using forward declaration.
* global variables `width`, `height` to retrieve the current width and height
* shape functions: `ellipse()`, `line()`, `point()`, `rect()`, `triangle()`.
* vertex, geometry and fragment shaders which contain e.g. the logic that allows to draw outlined shapes in a single render cycle.
* drawing style functions: `background()`, `clear()`, `ellipseMode()`, `fill()`, `noFill()`, `noStroke()`, `rectMode()`, `stroke()`, `strokeWeight()`.
* support of alpha channel for functions that deal with colors
* transformation functions: `applyMatrix()`, `resetMatrix()`, `rotate()`, `scale()`, `translate()`.
* constants: `HALF_PI`, `PI`, `QUARTER_PI`, `TWO_PI`.
* the functions `push()` and `pop()` which allow the current drawing style settings and matrix transformations to be temporarily saved on a stack.
* the possibility to directly modify window pixels using the global variable `pixels`.
* support for image loading.
* the possibility to directly modify image pixels using the member variable `Image::pixels`.
* convenience functions like: `millis()`, `random()`, `randomSeed()`.
* functions that allow to alter the control flow: `loop()`, `noLoop()`
* a function `redraw()` that ought to be used in conjunction with `noLoop`
* libraries: `glad`, `glfw`, `glm`, `stb_image`.
* a docsify documentation.
* cmake build scripts.
* fireworks example.
