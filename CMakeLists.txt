cmake_minimum_required(VERSION 3.25.1)
project(CGP)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_TESTING OFF CACHE BOOL "" FORCE)

add_subdirectory(dependencies/glew)
add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/glm)
add_subdirectory(dependencies/SOIL2)

add_executable(CGP src/main.cpp)

target_include_directories(CGP 
PUBLIC dependencies/glew/include
PUBLIC dependencies/glfw/include
PUBLIC dependencies/glm
)
target_link_directories(CGP
PRIVATE dependencies/glfw/src
PRIVATE dependencies/SOIL2
)

target_link_libraries(CGP glfw libglew_static glm)

set_property(TARGET CGP PROPERTY CXX_STANDARD 17)