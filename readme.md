# AutoBreak Clang tool

Automatically insert missing `break` statements to `switch`'s `case`-s.

## Build for use

```shell
cmake \
  -B build/release \
  -D CMAKE_BUILD_TYPE=Release \
  -D LLVM_DIR=<path/to/llvm> \
  -D CLANG_DIR=<path/to/clang>

cmake --build build/release --target auto_break
```

## Test

```shell
cmake \
  -B build/test \
  -D CMAKE_BUILD_TYPE=Debug \
  -D LLVM_DIR=<path/to/llvm> \
  -D CLANG_DIR=<path/to/clang> \
  -D AUTO_BREAK_ENABLE_TESTS=ON

cmake --build build/test --target test_empty_switch
```
