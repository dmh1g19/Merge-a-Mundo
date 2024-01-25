cmake_minimum_required(VERSION 3.10)

project(main)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)
include_directories(/usr/local/include/box2d)

set(SOURCES
    src/main.cpp
    src/window.cpp
    src/userInput.cpp
    src/rendering.cpp
    src/shape.cpp
    src/physics.cpp
    src/glad.c
)

add_executable(main ${SOURCES})

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

set(CMAKE_CXX_COMPILER "g++")

target_link_libraries(main OpenGL::GL glfw box2d)