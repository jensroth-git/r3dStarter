# Raylib + r3d Starter (CMake + MinGW)

This is a minimal template that fetches and builds the latest `r3d` (and its dependencies `raylib` and `assimp`) automatically via CMake's FetchContent. No manual cloning into `external/` is required.

## Prerequisites
- CMake 3.15+
- Git
- C/C++ toolchain (e.g., MinGW-w64 on Windows)
- Python 3 (required by `r3d` for shader processing)

## Quick start (Windows + MinGW)
```bash
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
```
Run the executable from `build/`.

## Pin versions (optional)
By default, the template fetches the latest from `master` branches. To pin stable versions, pass tags/commits:
```bash
cmake -S . -B build -G "MinGW Makefiles" \
  -DRAYLIB_GIT_TAG=5.5 \
  -DASSIMP_GIT_TAG=v5.3.1 \
  -DR3D_GIT_TAG=master
```

## Notes
- We build static libraries to avoid DLL issues on Windows.
- `raylib` is configured in a "minimal" mode compatible with `r3d` to avoid symbol clashes (model loaders disabled).
- If you prefer a different generator (e.g., Visual Studio), omit `-G "MinGW Makefiles"` and use the appropriate generator for your environment.

## Project structure
- `src/main.cpp`: Minimal sample that initializes `raylib` + `r3d` and renders a simple scene.
- `CMakeLists.txt`: Fetches and configures `raylib`, `assimp`, and `r3d`.

## Use as a template
- Copy this folder to start a new project, or use Github's "Use this template" feature.

