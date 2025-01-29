cmake_minimum_required(VERSION 3.21)
project(MyPacmanGame C)  # Change the project name here

# Set the C standard
set(CMAKE_C_STANDARD 99)

# Dependencies (Raylib)
# Ensure Raylib is linked properly
include(FetchContent)
set(RAYLIB_VERSION 4.5.0)  # Replace with the version you want to use
FetchContent_Declare(
        raylib
        URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
)
FetchContent_MakeAvailable(raylib)

# Source files
set(SOURCES
        src/main.c
        src/menu.c
        src/game.c
        include/assets.h src/assets.c src/record.c include/record.h src/difficulty.c include/difficulty.h)

# Include directories
include_directories(include)

# Add executable (change target name to MyPacmanGame)
add_executable(MyPacmanGame ${SOURCES})

# Link libraries
target_link_libraries(MyPacmanGame raylib)

# Copy the required DLLs to the build folder
# Ensure the Raylib DLLs are copied into the executable folder when building
add_custom_command(TARGET MyPacmanGame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${raylib_SOURCE_DIR}/src" $<TARGET_FILE_DIR:MyPacmanGame>   # Copy DLLs from the Raylib source directory
        )
