## Mandelbrot Example

This repository provides a portable C++11 implementation for generating images of the Mandelbrot set, a well-known fractal commonly used to demonstrate complex-number math, iterative algorithms, and performance characteristics in compute-heavy workloads.

The project renders the fractal into a bitmap image. The output resolution is configured at compile time, making it easy to build consistent artifacts and compare results across different systems, compilers, and optimization settings.

**Please Note**: This codebase is intended for learning and demonstration purposes. It is not designed, reviewed, or supported as production software, and it may omit features that production implementations typically require (for example: robust input validation, extensive configurability, and comprehensive error handling). The source code is provided under the Arm Education license.

## Build Requirements

Ensure you have a C++ compiler available. To build with CMake and run the unit tests, install CMake and GoogleTest development files.

## Build With Make

Create the output directories and build the single-threaded example in debug mode:

```bash
cd Mandelbrot-Example
mkdir -p images build
make single_thread DEBUG=1
```

To clean and rebuild:

```bash
make clean
make single_thread DEBUG=1
```

Build both examples:

```bash
make all DEBUG=1
```

The Makefile writes executables to `build/` and generated images to `images/`.

## Build With CMake

Configure a debug build:

```bash
cd Mandelbrot-Example
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
```

Build the single-threaded example:

```bash
cmake --build build --target single_thread
```

Build the parallel example:

```bash
cmake --build build --target parallel
```

Build all CMake targets:

```bash
cmake --build build
```

Debug executables are written to `build/` with a `_debug` suffix, for example `build/mandelbrot_single_thread_debug` and `build/mandelbrot_parallel_debug`.

## Run Tests

Build and run the GoogleTest unit tests:

```bash
cmake --build build --target mandelbrot_unit_tests
ctest --test-dir build --output-on-failure
```

Original Author: Kieran Hejmadi, Software and Academic Ecosystem Manager, Arm
