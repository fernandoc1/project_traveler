set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/../../webassembly_cmake_modules/WebassemblyToolchain.cmake")

project (nul_emscripten)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

FILE(GLOB NUL_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(nul ${NUL_SRC})

