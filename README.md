# Prog3

Starter repository for group programming exercises.

## Build

From the repository root, configure and build with CMake:

```sh
cmake -S . -B build
cmake --build build
```

On Windows with a multi-configuration generator, use `cmake --build build --config Debug`.
The executable is named `Aufgabe1` (or `Aufgabe1.exe` on Windows).

## Structure

- `Aufgabe1/main.cpp`: entry point for the first exercise. Main file
- `Aufgabe2/`: reserved for the second exercise. Replace `.gitkeep` when files are added.

When adding a new source file to an exercise, list it in that exercise's `CMakeLists.txt`.
When adding another exercise with its own `CMakeLists.txt`, add it to the root file with `add_subdirectory(...)`.
