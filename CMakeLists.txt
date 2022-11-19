cmake_minimum_required(VERSION 3.17)
project(EqualEngine)

set(CMAKE_CXX_STANDARD 17)

option(EQ_SHARED "Build the shared library" OFF)

if (WIN32)
    message(STATUS "> Applying windows settings")
    add_compile_options(/EHsc)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif (WIN32)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "> Applying debug settings")
    add_compile_definitions(DEBUG DEV_TOOLS)
endif (CMAKE_BUILD_TYPE STREQUAL "Debug")

add_subdirectory(equal)
add_subdirectory(example)
