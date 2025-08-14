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

# Define the SDL2 and SDL2_image archives for Linux.
set(SDL2_ARCHIVE "libs/thirdparty/win64/SDL2-devel-2.32.8-mingw.zip")
set(SDL2IMAGE_ARCHIVE "libs/thirdparty/win64/SDL2_image-devel-2.8.8-mingw.zip")

unset(MINGW_CONFIG_PATH)
if(CMAKE_SIZEOF_VOID_P EQUAL 4)
  set(MINGW_CONFIG_PATH "i686-w64-mingw32")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(MINGW_CONFIG_PATH "x86_64-w64-mingw32")
endif()

# Extract the SDL2 and SDL2_image archives.
file(ARCHIVE_EXTRACT INPUT "${CMAKE_CURRENT_LIST_DIR}/${SDL2_ARCHIVE}"
     DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/_deps/")
file(ARCHIVE_EXTRACT INPUT "${CMAKE_CURRENT_LIST_DIR}/${SDL2IMAGE_ARCHIVE}"
     DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/_deps/")

# Add the cmake directories for SDL2 and SDL2_image to the CMAKE_PREFIX_PATH.
list(APPEND CMAKE_PREFIX_PATH
     "${CMAKE_CURRENT_BINARY_DIR}/_deps/SDL2-2.32.8/cmake")
list(APPEND CMAKE_PREFIX_PATH
     "${CMAKE_CURRENT_BINARY_DIR}/_deps/SDL2_image-2.8.8/cmake")

# Find the SDL2 and SDL2_image packages.
find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
find_package(SDL2_image REQUIRED CONFIG REQUIRED COMPONENTS SDL2_image)

# Add the subdirectories for SDL2 and SDL2_image to build them.
set(SDL2_DEP_DIR
    "${CMAKE_CURRENT_BINARY_DIR}/_deps/SDL2-2.32.8/${MINGW_CONFIG_PATH}")
set(SDL2IMAGE_DEP_DIR
    "${CMAKE_CURRENT_BINARY_DIR}/_deps/SDL2_image-2.8.8/${MINGW_CONFIG_PATH}")
set(SDL2_BIN_DIR "${SDL2_DEP_DIR}/bin")
set(SDL2IMAGE_BIN_DIR "${SDL2IMAGE_DEP_DIR}/bin")

# unset(SDL2_INCLUDE_DIRS) list(APPEND SDL2_INCLUDE_DIRS
# "${SDL2_DEP_DIR}/include/SDL2" "${SDL2IMAGE_DEP_DIR}/include/SDL2")
#
# unset(SDL2_LIBRARY_DIRS) list(APPEND SDL2_LIBRARY_DIRS "${SDL2_DEP_DIR}/lib"
# "${SDL2IMAGE_DEP_DIR}/lib")

# list(APPEND SDL2_LIBRARY_DIRS "${SDL2_DEP_DIR}/lib" "${SDL2IMAGE_DEP_DIR}/lib"
# "${SDL2_BIN_DIR}/SDL2.dll" "${SDL2IMAGE_BIN_DIR}/SDL2_image.dll")

# find_library( SDL2MAIN_LIBRARY NAMES SDL2main PATHS ${SDL2_LIBRARY_DIRS})
# find_library( SDL2_LIBRARY NAMES SDL2 PATHS ${SDL2_LIBRARY_DIRS})
# find_library( SDL2IMAGE_LIBRARY NAMES SDL2_image PATHS ${SDL2_LIBRARY_DIRS})

# Add source code to this project's executable with Windows subsystem.
add_executable(${CMAKE_PROJECT_NAME} WIN32 ${SRC_CODE})

# Set the include path for compiling the target. Include the current binary
# directory for the config file which defines version info.
target_include_directories(
  ${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
                                ${ABEARGS_INCLUDE_DIR} ${SDL2_INCLUDE_DIRS})

# Link the following libraries into the target executable.
target_link_libraries(
  ${CMAKE_PROJECT_NAME} PRIVATE mingw32 AbeArgs SDL2::SDL2main SDL2::SDL2
                                SDL2_image::SDL2_image)

add_custom_command(
  TARGET ${CMAKE_PROJECT_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy "${SDL2_BIN_DIR}/SDL2.dll"
          "$<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>"
  COMMENT "Copying SDL2.dll to output directory")

add_custom_command(
  TARGET ${CMAKE_PROJECT_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy "${SDL2IMAGE_BIN_DIR}/SDL2_image.dll"
          "$<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>"
  COMMENT "Copying SDL2_image.dll to output directory")
