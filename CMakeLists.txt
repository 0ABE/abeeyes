# 
#        d8888 888               8888888888
#       d88888 888               888
#      d88P888 888               888
#     d88P 888 88888b.   .d88b.  8888888   888  888  .d88b.  .d8888b
#    d88P  888 888 "88b d8P  Y8b 888       888  888 d8P  Y8b 88K
#   d88P   888 888  888 88888888 888       888  888 88888888 "Y8888b.
#  d8888888888 888 d88P Y8b.     888       Y88b 888 Y8b.          X88
# d88P     888 88888P"   "Y8888  8888888888 "Y88888  "Y8888   88888P'
#                                               888
# Somebody's watching me 8-)               Y8b d88P
#                                           "Y88P"
# Copyright (c) 2025, Abe Mishler
# Licensed under the Universal Permissive License v 1.0
# as shown at https://oss.oracle.com/licenses/upl/.
# 

cmake_minimum_required(VERSION 3.22.1)
message(STATUS "Using CMake version " ${CMAKE_VERSION})

project("AbeEyes" VERSION 0.1.250419)

configure_file(
  "${CMAKE_SOURCE_DIR}/AbeEyesConfig.h.in" 
  "${CMAKE_BINARY_DIR}/AbeEyesConfig.h"
)

# ---- Enable C++20 ----------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# ---- Stick to the standard -------------------------
set(CMAKE_CXX_EXTENSIONS OFF)
# ----------------------------------------------------

# ---- Choose a build type ---------------------------
#
# NOTE: To set a build type using CMake Tools (VSCode
# extension), comment these lines. If not using CMake
# Tools, uncomment the following to set a build type.
# 
# * * Don't forget the #define for Debug builds. * * *
#
# ---- Debug (with a #define DEBUG_BUILD) ------------
# set(CMAKE_BUILD_TYPE Debug)
# add_compile_definitions(DEBUG_BUILD)
# ---- Release ---------------------------------------
# set(CMAKE_BUILD_TYPE Release)
# ----------------------------------------------------

# ---- Source code defined  --------------------------
list(APPEND SRC_CODE
  "src/graphics/Grob.cpp"
  "src/graphics/Grob.h"
  "src/graphics/LoopType.h"
  "src/graphics/Resources.cpp"
  "src/graphics/Resources.h"
  "src/graphics/Sprite.cpp"
  "src/graphics/Sprite.h"
  "src/graphics/SpriteList.cpp"
  "src/graphics/SpriteList.h"
  "src/graphics/Texture.cpp"
  "src/graphics/Texture.h"
  "src/Eyeball.cpp"
  "src/Eyeball.h"
  "src/MouseAttrs.h"
  "src/System.cpp"
  "src/System.h"
  "src/main.cpp"
)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)


# Add source code to this project's executable.
add_executable(${CMAKE_PROJECT_NAME} ${SRC_CODE})

# Relies on pkg-config to find SDL2 and SDL2IMAGE.
# Seems easier than a special cross platform cmake/module script right now.
# > brew install pkgconf
# > pkg-config --cflags --libs SDL2 SDL2_image
INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

message(STATUS "SDL2 include dir: ${SDL2_INCLUDE_DIRS}")
message(STATUS "SDL2 library dir: ${SDL2_LIBRARY_DIRS}")
message(STATUS "SDL2 library: ${SDL2_LIBRARIES}")
message(STATUS "SDL2_image library: ${SDL2IMAGE_LIBRARIES}")

# Set the include path for compiling the target.
# Include the current binary directory for the config file which defines version info.
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC 
                           ${CMAKE_CURRENT_BINARY_DIR}
                           ${SDL2_INCLUDE_DIRS}
                           ${SDL2IMAGE_INCLUDE_DIRS})

# Set the library path for compiling the target.
target_link_directories(${CMAKE_PROJECT_NAME} PUBLIC
                        ${SDL2_LIBRARY_DIRS})

# Link the following libraries into the target executable.
target_link_libraries(${CMAKE_PROJECT_NAME} SDL2 SDL2_image)

# Link the X11 libs for Linux.
if (CMAKE_SYSTEM_NAME MATCHES "Linux")
  target_link_libraries(${CMAKE_PROJECT_NAME} X11)
endif()
