cmake_minimum_required(VERSION 3.25.1)
project(CGP)

add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/glm)
add_subdirectory(dependencies/SOIL2)

add_executable(CGP src/main.cpp)
target_include_directories(CGP PRIVATE dependencies/glew/include)