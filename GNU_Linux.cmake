# Find the X11 libraries for Linux.
find_package(X11 REQUIRED)
if(NOT X11_FOUND)
  message(FATAL_ERROR "X11 libraries not found")
endif()

# Define the SDL2 and SDL2_image archives for Linux.
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
  ${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR} ${X11_INCLUDE_DIRS}
                                ${ABEARGS_INCLUDE_DIR} ${SDL2_INCLUDE_DIRS})

# Link the following libraries into the target executable.
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE AbeArgs SDL2 SDL2_image
                                                    ${X11_LIBRARIES})
