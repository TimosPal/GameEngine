# Define the sandbox executable
add_executable(Sandbox "test.cpp")

# Link the GameEngine library to the Sandbox executable
target_link_libraries(Sandbox PRIVATE GameEngine)

# Include directories for Sandbox
target_include_directories(Sandbox PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR}/sandbox)
