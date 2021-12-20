# AutoBreak tool

Automatically insert missing `break` statements to `switch`'s `case`-s.

## Build

```shell
cmake -B build/release -D CMAKE_BUILD_TYPE=Release -D LLVM_DIR=<path/to/llvm>
cmake --build build/release --target auto_break
```
