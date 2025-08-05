# Define the SDL2 and SDL2_image archives for Windows.
set(SDL2_ARCHIVE "libs/thirdparty/win64/SDL2-devel-2.32.8-VC.zip")
set(SDL2IMAGE_ARCHIVE "libs/thirdparty/win64/SDL2_image-devel-2.8.8-VC.zip")

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

# cmake-format: off
# find_package(SDL2 2.32.8 COMPONENTS SDL2 REQUIRED)
# find_package(SDL2_image 2.8.8 COMPONENTS SDL2_image REQUIRED)
# cmake-format: on

# Add source code to this project's executable.
add_executable(${CMAKE_PROJECT_NAME} ${SRC_CODE})

# Set a Windows subsystem instead of console. This is necessary for the WinMain
# entry point. This will prevent a console window from appearing when the
# application is run.
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES LINK_FLAGS
                                                       "/SUBSYSTEM:WINDOWS")

# Set the include path for compiling the target. Include the current binary
# directory for the config file which defines version info.
target_include_directories(
  ${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
                                ${ABEARGS_INCLUDE_DIR} ${SDL2_INCLUDE_DIRS})

# SDL2main must be linked first on Windows.
target_link_libraries(
  ${CMAKE_PROJECT_NAME} PRIVATE AbeArgs SDL2::SDL2main SDL2::SDL2
                                SDL2_image::SDL2_image)
