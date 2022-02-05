add_library (CatCutifier "app/my_app.cpp" "app/my_app.h")
target_include_directories(CatCutifier PUBLIC app)

# Should install library properly here, but I'm focusing on just the docs