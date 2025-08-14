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

# Define the SDL2 and SDL2_image archives for macOS (shared with Linux).
set(SDL2_ARCHIVE "libs/thirdparty/linux/SDL2-2.32.8.tar.gz")
set(SDL2IMAGE_ARCHIVE "libs/thirdparty/linux/SDL2_image-2.8.8.tar.gz")

# Extract the SDL2 and SDL2_image archives.
file(ARCHIVE_EXTRACT INPUT "${CMAKE_CURRENT_LIST_DIR}/${SDL2_ARCHIVE}"
     DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/_deps/")
file(ARCHIVE_EXTRACT INPUT "${CMAKE_CURRENT_LIST_DIR}/${SDL2IMAGE_ARCHIVE}"
     DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/_deps/")

# Add the subdirectories for SDL2 and SDL2_image to build them.
set(SDL2_DEP_DIR "${CMAKE_CURRENT_BINARY_DIR}/_deps/SDL2-2.32.8")
set(SDL2IMAGE_DEP_DIR "${CMAKE_CURRENT_BINARY_DIR}/_deps/SDL2_image-2.8.8")
set(SDL2_BUILD_DIR "${SDL2_DEP_DIR}/build")
set(SDL2IMAGE_BUILD_DIR "${SDL2IMAGE_DEP_DIR}/build")
add_subdirectory("${SDL2_DEP_DIR}" "${SDL2_BUILD_DIR}")
add_subdirectory("${SDL2IMAGE_DEP_DIR}" "${SDL2IMAGE_BUILD_DIR}")

# Add source code to this project's executable.
add_executable(${CMAKE_PROJECT_NAME} ${SRC_CODE})

# Set the include path for compiling the target. Include the current binary
# directory for the config file which defines version info.
target_include_directories(
  ${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR} 
                                ${ABEARGS_INCLUDE_DIR} ${SDL2_INCLUDE_DIRS})

# Link the following libraries into the target executable, including the
# CoreGraphics and Foundation libs for macOS.
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE AbeArgs SDL2 SDL2_image
                                                    "-framework CoreGraphics"
                                                    "-framework Foundation")
