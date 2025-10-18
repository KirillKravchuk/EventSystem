## Requirements

- CMake **3.16+**
- C++ compiler
  - **Linux:** GCC or Clang
  - **Windows:** MSVC
- Optional: `make` or `ninja` build system

## Build Instructions:

## Linux (WSL / Ubuntu)

### Create build directory

mkdir -p build
cd build

### Configure the project

cmake ..

### Build

make -j

### Run the executable
../out/EventSystem


## Windows (MSVC + CMake presets)

### Configure
cmake --preset x64-debug

### Build
cmake --build out/build/x64-debug

### Run 
out\build\x64-debug\EventSystem.exe