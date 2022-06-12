#! /bin/bash

TEST_DIR=$(dirname $(readlink -f $0))

cd ${TEST_DIR}

OUTPUT_DIR=../tmp

rm -rf ${OUTPUT_DIR}
mkdir ${OUTPUT_DIR}

LIBTRAVELER=${OUTPUT_DIR}/libtraveler.so
LIBTRAVELER_LUA=${OUTPUT_DIR}/libtraveler_lua.so

OBJECT_FILES=$(find ../build -iname "*.o" | grep -v "lua" | grep -v "main.cpp.o")
LUA_OBJECT_FILES=$(find ../build -iname "*.o" | grep "lua")

LIBRARIES="glew glx openal opengl glesv2 ogg vorbis vorbisfile libpng sdl2 SDL2_image SDL2_ttf"
INCLUDE_DIRS="-I../src/ -I../src/utils/src/ -I../src/luabind/ -I../webassembly_deps/lua/"
LIB_INCLUDE_FLAGS=$(pkg-config --cflags ${LIBRARIES})
LIB_LINK_FLAGS=$(pkg-config --cflags --libs ${LIBRARIES})

BATTLE_TEST_O=${OUTPUT_DIR}/battle_test.o

g++ -Wl,--start-group ${OBJECT_FILES} ${LIB_LINK_FLAGS} -Wl,--end-group -fPIC -shared -o ${LIBTRAVELER}
g++ -Wl,--start-group ${LUA_OBJECT_FILES} ${LIB_LINK_FLAGS} -Wl,--end-group -fPIC -shared -o ${LIBTRAVELER_LUA}
g++ ${INCLUDE_DIRS} ${LIB_INCLUDE_FLAGS} -c battle_test.cpp -o ${BATTLE_TEST_O}
g++ -Wl,--start-group ${BATTLE_TEST_O} ${LIBTRAVELER} ${LIBTRAVELER_LUA} ${LIB_LINK_FLAGS} -Wl,--end-group


