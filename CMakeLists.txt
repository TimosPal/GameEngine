cmake_minimum_required(VERSION 3.12)

project(GameEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Recursively find all .cpp and .hpp files in src directory
file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE ENGINE_HEADERS CONFIGURE_DEPENDS src/*.hpp)
set(ENGINE_FILES ${ENGINE_SOURCES} ${ENGINE_HEADERS})

# Create GameEngine as a library
add_library(GameEngine ${ENGINE_FILES})

# GLFW Build Options
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE) # Force static linking

# Add GLFW as a subdirectory
add_subdirectory(external/glfw)
add_subdirectory(external/spdlog)

# Link GameEngine with GLFW and OpenGL
target_link_libraries(GameEngine PUBLIC glfw spdlog::spdlog)

# Include directories
target_include_directories(GameEngine PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

# Add the Sandbox subdirectory
add_subdirectory(sandbox)