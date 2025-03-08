cmake_minimum_required(VERSION 3.12)

# TODO: Hot reload support

project ("GameEngine")

# Find source files
file(GLOB SOURCES 
    "GameEngine.cpp"
    "GameObjects/*.cpp"
    "GameObjects/*.h"
    "misc/*.cpp"
    "misc/*.h"
)

# Add source to this project's executable.
add_executable(GameEngine ${SOURCES})

set_property(TARGET GameEngine PROPERTY CXX_STANDARD 20)

target_include_directories(GameEngine PRIVATE
    ${CMAKE_SOURCE_DIR}
    # Add any other directories you need here
)