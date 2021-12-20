cmake_minimum_required(VERSION 3.18)

project(libtooling_auto_break)

# ------------------------------------------------------------------------------
# Public options.

option(AUTO_BREAK_ENABLE_TESTS "Build tests for `auto_break` tool" OFF)

# ------------------------------------------------------------------------------
# CMake setup.

include(cmake/ProjectSettings.cmake)
include(cmake/AutoBreakTests.cmake)

# ------------------------------------------------------------------------------
# Dependencies.

# LLVM.

find_package(LLVM REQUIRED CONFIG)
llvm_map_components_to_libnames(LLVM_LIBRARIES all)

# ------------------------------------------------------------------------------
# `auto_break` tool.

add_executable(auto_break
  src/main.cpp
)
target_include_directories(auto_break
  PRIVATE src
  PRIVATE ${LLVM_INCLUDE_DIRS}
)
target_link_libraries(auto_break
  PRIVATE ${LLVM_LIBRARIES}
)

# ------------------------------------------------------------------------------
# Tests.

if (${AUTO_BREAK_ENABLE_TESTS})
  add_subdirectory(tests)
endif()
