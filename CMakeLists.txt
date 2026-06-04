# CMake project
cmake_minimum_required(VERSION 4.1.2)
project(raytracing-in-one-weekend)

enable_language(CXX)

# Main source files
set( SRC_FILES
    "src/main.cpp"
)
add_executable(main ${SRC_FILES})

target_include_directories(main PRIVATE "src/")
target_include_directories(main PRIVATE "vendor/")