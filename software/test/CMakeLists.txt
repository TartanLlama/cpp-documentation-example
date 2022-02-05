add_definitions(-DFOO -DBAR)
add_executable (UnitTest.exe "test.cpp" )
target_link_libraries(UnitTest.exe PUBLIC UnitTestLib)

# target_include_directories(UnitTest PUBLIC ../app)

