# the name of the target operating system
set(CMAKE_SYSTEM_NAME Generic)

# which compilers to use for C and C++
SET(CMAKE_C_COMPILER "emcc")
SET(CMAKE_CXX_COMPILER "emcc")

SET(USE_FLAGS "\
-s SDL2_IMAGE_FORMATS='[\"png\"]' \
-s USE_BOOST_HEADERS=1 \
-s USE_FREETYPE=1 \
-s USE_OGG=1 \
-s USE_LIBPNG=1 \
-s USE_OGG=1 \
-s USE_SDL=2 \
-s USE_SDL_IMAGE=2 \
-s USE_SDL_MIXER=2 \
-s USE_SDL_TTF=2 \
-s USE_VORBIS=1 \
-s WASM=1 \
")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${USE_FLAGS}")
set(CMAKE_EXECUTABLE_SUFFIX .html)

# where is the target environment located
set(CMAKE_FIND_ROOT_PATH $ENV{EMSDK}/upstream/emscripten/cache/sysroot/)

# adjust the default behavior of the FIND_XXX() commands:
# search programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# search headers and libraries in the target environment
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

#SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/webassembly_cmake_modules/" "$ENV{EMSDK}/upstream/emscripten/cmake/Modules/")
#message(">>> CMAKE_MODULE_PATH=${CMAKE_MODULE_PATH}")

SET(SDL2_INCLUDE_DIR "${EMSDK}/upstream/emscripten/cache/sysroot/include/SDL2")
SET(SDL2MAIN_LIBRARY "")

