set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/../../webassembly_cmake_modules/WebassemblyToolchain.cmake")

project (lua_emscripten)
cmake_minimum_required(VERSION 2.8)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s LLD_REPORT_UNDEFINED")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s LLD_REPORT_UNDEFINED")

add_definitions(-DLUA_COMPAT_5_2)

FILE(GLOB LUA_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

add_library(lua ${LUA_SRC})

