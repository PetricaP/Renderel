# Project definition

cmake_minimum_required(VERSION 3.0.0)
project(Renderel)

# Setting up some flags

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -pedantic -Wall -Wextra -g")

file(GLOB_RECURSE PROJECT_SOURCES "src/*.cpp")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# Adding GLEW

add_subdirectory(${CMAKE_SOURCE_DIR}/lib/glew/build/cmake)

# Adding GLFW

set( GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE )

add_subdirectory(${CMAKE_SOURCE_DIR}/lib/glfw)

#Adding Renderel

add_executable(Renderel ${PROJECT_SOURCES})

target_include_directories(Renderel PUBLIC ${PROJECT_SOURCE_DIR}/lib/glew/include)
target_link_libraries(Renderel glew_s glfw)