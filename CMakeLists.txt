# Project definition

cmake_minimum_required(VERSION 3.0.0)
project(Renderel)

# Setting up some flags

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -pedantic -Wall -Wextra -g")

if (UNIX)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    set(OpenGL_GL_PREFERENCE LEGACY)
endif (UNIX)

file(GLOB_RECURSE PROJECT_SOURCES "src/*.cpp")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# Adding GLEW

set( BUILD_SHARED_LIBS FALSE )
set( BUILD_UTILS OFF CACHE BOOL "" FORCE )

add_subdirectory(${CMAKE_SOURCE_DIR}/lib/glew/build/cmake)
set_target_properties(glew PROPERTIES EXCLUDE_FROM_ALL 1 EXCLUDE_FROM_DEFAULT_BUILD 1)

# Adding GLFW

set( GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE )

add_subdirectory(${CMAKE_SOURCE_DIR}/lib/glfw)

#Adding Renderel

add_executable(Renderel ${PROJECT_SOURCES})

target_include_directories(Renderel PUBLIC ${PROJECT_SOURCE_DIR}/lib/glew/include ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(Renderel glew_s glfw)
