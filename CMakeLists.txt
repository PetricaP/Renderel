# Project definition

cmake_minimum_required(VERSION 3.0.0)
project(Renderel)

# Setting up some flags

if ( CMAKE_BUILD_TYPE STREQUAL "" )
        # CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
        # differentiation between debug and release builds.
        set(
                CMAKE_BUILD_TYPE
                        "Debug"
                CACHE STRING
                        "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) \"Debug\" \"Release\" \"RelWithDebInfo\" \"MinSizeRel\"."
                FORCE
        )
endif ( CMAKE_BUILD_TYPE STREQUAL "" )

if ( CMAKE_BUILD_TYPE STREQUAL "Release" )
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
        add_definitions( /O2 )
    else()
        add_definitions( -O3 )
    endif()
endif ( CMAKE_BUILD_TYPE STREQUAL "Release" )

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  # using Clang
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -fms-extensions  -Wall -Wextra -g")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  # using GCC
    set(ignoreMe "${QT_QMAKE_EXECUTABLE}")
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    set(OpenGL_GL_PREFERENCE LEGACY)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -fms-extensions -Wall -Wextra -g")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
  # using Intel C++ 
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  # using Visual Studio C++
  	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif()

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# Adding GLEW

set(BUILD_SHARED_LIBS FALSE)
set(BUILD_UTILS OFF CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_SOURCE_DIR}/lib/glew/build/cmake)
set_target_properties(glew PROPERTIES EXCLUDE_FROM_ALL 1 EXCLUDE_FROM_DEFAULT_BUILD 1)

# Adding GLFW

set( GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE )

add_subdirectory(${CMAKE_SOURCE_DIR}/lib/glfw)

#Adding Renderel

file(GLOB_RECURSE PROJECT_SOURCES "src/*.c*")
file(GLOB_RECURSE PROJECT_HEADERS "include/*.h*")
file(GLOB SHADERS shaders/*.frag shaders/*.vert shaders/*.glsl)

add_executable(Renderel ${SHADERS} ${PROJECT_SOURCES} ${PROJECT_HEADERS})

target_include_directories(Renderel PUBLIC ${PROJECT_SOURCE_DIR}/lib/glew/include PUBLIC ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/include/vendor)

target_link_libraries(Renderel glew_s glfw)
