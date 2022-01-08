set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/../../webassembly_cmake_modules/WebassemblyToolchain.cmake")

project (lua_emscripten)
cmake_minimum_required(VERSION 2.8)

FILE(GLOB LUA_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

add_library(lua ${LUA_SRC})

