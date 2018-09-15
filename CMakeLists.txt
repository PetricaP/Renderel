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

# Adding STB

file(GLOB STB_HEADERS "lib/stb/stb_*.cpp")
file(GLOB STB_SOURCES "lib/stb/stb_*.h")

set(STB_FILES ${STB_HEADERS} ${STB_SOURCES})

# Adding ImGui

file(GLOB IMGUI_HEADERS "lib/imgui/im*.cpp"
	"lib/imgui/examples/imgui_impl_glfw.h"
	"lib/imgui/examples/imgui_impl_opengl2.h"
	"lib/imgui/examples/imgui_impl_opengl3.h")
file(GLOB IMGUI_SOURCES "lib/imgui/im*.h"
	"lib/imgui/examples/imgui_impl_glfw.cpp"
	"lib/imgui/examples/imgui_impl_opengl2.cpp"
	"lib/imgui/examples/imgui_impl_opengl3.cpp")

set(IMGUI_FILES ${IMGUI_HEADERS} ${IMGUI_SOURCES})

#Adding Renderel

file(GLOB_RECURSE PROJECT_SOURCES "src/*.c*")
file(GLOB_RECURSE PROJECT_HEADERS "include/*.h*")
file(GLOB SHADERS "shaders/*.frag" "shaders/*.vert" "shaders/*.glsl")

set(PROJECT_FILES ${PROJECT_HEADERS} ${PROJECT_SOURCES} ${SHADERS})

add_executable(Renderel ${PROJECT_FILES} ${STB_FILES} ${IMGUI_FILES})

target_include_directories(Renderel PUBLIC ${PROJECT_SOURCE_DIR}/lib/glfw/include)
target_include_directories(Renderel PUBLIC ${PROJECT_SOURCE_DIR}/lib/glew/include)
target_include_directories(Renderel PUBLIC ${PROJECT_SOURCE_DIR}/lib/stb)
target_include_directories(Renderel PUBLIC ${PROJECT_SOURCE_DIR}/lib/imgui)
target_include_directories(Renderel PUBLIC ${PROJECT_SOURCE_DIR}/lib/imgui/examples/)
target_include_directories(Renderel PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(Renderel glew_s glfw)

target_compile_definitions(Renderel PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLEW)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	target_compile_definitions(Renderel PUBLIC _CRT_SECURE_NO_WARNINGS)
endif()
