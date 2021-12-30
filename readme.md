# AutoBreak

AutoBreak is a ClangTool that automatically inserts missing `break` statements
to `case`-s of the `switch` statement.

## When AutoBreak inserts `break` statements?

When case has:

* No `break` statement (obviously).
* No `return` statement.
* No `[[fallthrough]]` attribute.

## Known limitations

Currently, AutoBreak is unaware of:

* `[[noreturn]]` function calls.

## Build for use

```shell
cmake \
  -B build/release \
  -D CMAKE_BUILD_TYPE=Release \
  -D LLVM_DIR=<path/to/llvm> \
  -D CLANG_DIR=<path/to/clang>

cmake --build build/release --target auto-break
```

## Test

Tests are unavailable yet.

<details>

```shell
cmake \
  -B build/test \
  -D CMAKE_BUILD_TYPE=Debug \
  -D LLVM_DIR=<path/to/llvm> \
  -D CLANG_DIR=<path/to/clang> \
  -D AUTO_BREAK_ENABLE_TESTS=ON

cmake --build build/test --target test_empty_switch
```

</details>
