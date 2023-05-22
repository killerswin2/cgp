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

file(GLOB SOURCES_DEBUG "src/debug/*.hpp" "src/debug/*.cpp")
file(GLOB SOURCES_SHADER "src/shader/*.hpp" "src/shader/*.cpp")
file(GLOB SOURCES_MODEL "src/model/*.hpp" "src/model/*.cpp")
file(GLOB SOURCES_APPLICATION "src/application/*.hpp" "src/application/*.cpp")


add_executable(CGP src/main.cpp ${SOURCES_DEBUG} ${SOURCES_SHADER} ${SOURCES_MODEL} ${SOURCES_APPLICATION})

target_include_directories(CGP 
PUBLIC dependencies/glew/include
PUBLIC dependencies/glfw/include
PUBLIC dependencies/glm
PUBLIC dependencies/SOIL2/src
)
target_link_directories(CGP
PRIVATE dependencies/glfw/src
PRIVATE dependencies/SOIL2
)

target_link_libraries(CGP glfw libglew_static glm soil2)

set_target_properties(CGP PROPERTIES CXX_STANDARD 17)