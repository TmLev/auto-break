# ------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.18)

project(auto_break)

# ------------------------------------------------------------------------------
# Public options.

option(AUTO_BREAK_ENABLE_TESTS "Build tests for `auto_break` tool" OFF)

# ------------------------------------------------------------------------------
# CMake setup.

include(cmake/ProjectSettings.cmake)
include(cmake/AutoBreakTests.cmake)

# ------------------------------------------------------------------------------
# Dependencies.

# LLVM & Clang.

find_package(LLVM CONFIG REQUIRED)
llvm_map_components_to_libnames(LLVM_LIBRARIES Support)
message(STATUS "[auto_break] Found LLVM in ${LLVM_DIR}")
message(STATUS "[auto_break] LLVM libraries: ${LLVM_LIBRARIES}")

find_package(CLANG CONFIG REQUIRED)
message(STATUS "[auto_break] Found Clang in ${CLANG_DIR}")

# ------------------------------------------------------------------------------
# `auto_break` tool.

add_executable(auto_break
  src/main.cpp
  src/details/impl.cpp
)
target_include_directories(auto_break
  PRIVATE src
)

# Add LLVM & Clang.

target_include_directories(auto_break
  SYSTEM
  PRIVATE
    ${LLVM_INCLUDE_DIRS}
    ${CLANG_INCLUDE_DIRS}
)
target_link_libraries(auto_break
  PRIVATE
    ${LLVM_LIBRARIES}
    clangAST
    clangBasic
    clangDriver
    clangFrontend
    clangRewriteFrontend
    clangSerialization
    clangStaticAnalyzerFrontend
    clangTooling
    clangToolingSyntax
)

# ------------------------------------------------------------------------------
# `auto_break` tests.

if (${AUTO_BREAK_ENABLE_TESTS})
  add_subdirectory(tests)
endif()
