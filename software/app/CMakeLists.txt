add_library (UnitTestLib "a.cpp" "b.cpp")
add_executable (MySuperProject "app.cpp" "a.cpp" "b.cpp")
target_include_directories(MySuperProject PUBLIC .)

# Should install library properly here, but I'm focusing on just the docs