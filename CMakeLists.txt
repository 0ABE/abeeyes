# cmake-format: off
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
# cmake-format: on

cmake_minimum_required(VERSION 3.22.1)
message(STATUS "Using CMake version " ${CMAKE_VERSION})

include(FetchContent)

project("AbeEyes" VERSION 0.1.250616)
configure_file("${CMAKE_SOURCE_DIR}/AbeEyesConfig.h.in"
               "${CMAKE_BINARY_DIR}/AbeEyesConfig.h")

# ---- Enable C++20 ----------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# ---- Stick to the standard -------------------------
set(CMAKE_CXX_EXTENSIONS OFF)
# ----------------------------------------------------

unset(GNU_LINUX)
if(CMAKE_SYSTEM_NAME MATCHES "Linux" AND CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  set(GNU_LINUX TRUE)
endif()

unset(GNU_WINDOWS)
if(CMAKE_SYSTEM_NAME MATCHES "Windows" AND CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  set(GNU_WINDOWS TRUE)
endif()

unset(MSVC_WINDOWS)
if(CMAKE_SYSTEM_NAME MATCHES "Windows" AND CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  set(MSVC_WINDOWS TRUE)
endif()

# cmake-format: off
# Choose the build type.
set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type: Release" FORCE)
# set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type: Debug" FORCE)
# cmake-format: on

# Add compile definitions based on the build type. This will allow us to
# conditionally compile code based on the build type.
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  message(STATUS "Building in Debug mode")
  add_compile_definitions(DEBUG_BUILD)
else()
  message(STATUS "Building in Release mode")
  add_compile_definitions(RELEASE_BUILD)
endif()

# ---- Source code defined  --------------------------
list(
  APPEND
  SRC_CODE
  "src/graphics/Grob.cpp"
  "src/graphics/Resources.cpp"
  "src/graphics/Sprite.cpp"
  "src/graphics/SpriteList.cpp"
  "src/graphics/Texture.cpp"
  "src/platform/AbstractSystem.cpp"
  "src/states/BlinkState.cpp"
  "src/states/EyeState.cpp"
  "src/states/LookState.cpp"
  "src/Eyeball.cpp"
  "src/Timer.cpp"
  "src/main.cpp")

if(CMAKE_SYSTEM_NAME MATCHES "Darwin")
  list(APPEND SRC_CODE "src/platform/MacSystem.cpp")
endif()

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
  list(APPEND SRC_CODE "src/platform/LinuxSystem.cpp")
endif()

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
  list(APPEND SRC_CODE "src/platform/WinSystem.cpp")
endif()

# cmake-format: off
# Fetch the AbeArgs library.
# To view stdout and stderr when running the app, use the following PowerShell
# command with any valid command line argument like --help or --version:
# Start-Process -RedirectStandardOutput stdout.log .\AbeEyes.exe --help
# cmake-format: on
FetchContent_Declare(
  AbeArgs
  GIT_REPOSITORY https://github.com/0ABE/abeargs.git
  GIT_TAG origin/master
  SOURCE_SUBDIR abeargs_lib)
FetchContent_MakeAvailable(AbeArgs)
message(STATUS "AbeArgs include dir: " ${ABEARGS_INCLUDE_DIR})

if(GNU_LINUX)
  message(STATUS "Building on GNU/Linux system: " ${CMAKE_SYSTEM_NAME})
  include("GNU_Linux.cmake")
elseif(GNU_WINDOWS)
  message(STATUS "Building on Windows system: " ${CMAKE_SYSTEM_NAME})
  include("GNU_Windows.cmake")
elseif(MSVC_WINDOWS)
  message(STATUS "Building on Windows system: " ${CMAKE_SYSTEM_NAME})
  include("MSVC_Windows.cmake")
endif()

# cmake-format: off
# if(CMAKE_SYSTEM_NAME MATCHES "Darwin")
#   # Link the CoreGraphics and Foundation libs for macOS.
#   target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE "-framework CoreGraphics"
#                                                       "-framework Foundation")
# endif()
# cmake-format: on
