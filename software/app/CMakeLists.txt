add_executable (${CMAKE_PROJECT_NAME} "main.cpp" "Name.cpp")
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC .)

# Should install library properly here, but I'm focusing on just the docs