# Define the sandbox executable
add_executable(Sandbox "test.cpp")

# Link the GameEngine library to the Sandbox executable
target_link_libraries(Sandbox PRIVATE GameEngine)

# Include directories for Sandbox
target_include_directories(Sandbox PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

# Ensure assets copy every time
add_custom_target(CopyAssets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
    ${CMAKE_BINARY_DIR}/sandbox/assets
)

# Make sure the assets are copied before Sandbox builds
add_dependencies(Sandbox CopyAssets)