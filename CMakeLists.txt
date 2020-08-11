cmake_minimum_required(VERSION 3.9)
project(scripts)

add_subdirectory(godot-cpp)

include_directories(src godot-cpp/include godot-cpp/include/core godot-cpp/include/gen godot-cpp/godot_headers)
aux_source_directory(src SOURCES)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
add_library(scripts
        SHARED
        ${SOURCES})
target_link_libraries(scripts godot-cpp)

set(BITS 32)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(BITS 64)
endif(CMAKE_SIZEOF_VOID_P EQUAL 8)

if (CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE Debug)
endif(CMAKE_BUILD_TYPE STREQUAL "")

if (NOT CMAKE_BUILD_TYPE MATCHES Debug)
    add_compile_options(-O3)
endif(NOT CMAKE_BUILD_TYPE MATCHES Debug)

string(TOLOWER ${CMAKE_SYSTEM_NAME} SYSTEM_NAME)
string(TOLOWER ${CMAKE_BUILD_TYPE} BUILD_TYPE)

if(ANDROID)
    # Added the android abi after system name
    set(SYSTEM_NAME ${SYSTEM_NAME}.${ANDROID_ABI})
    # Android does not have the bits at the end if you look at the main godot repo build
    set_property(TARGET ${PROJECT_NAME} PROPERTY OUTPUT_NAME "${PROJECT_NAME}.${SYSTEM_NAME}")
else()
    set_property(TARGET ${PROJECT_NAME} PROPERTY OUTPUT_NAME "${PROJECT_NAME}.${SYSTEM_NAME}.${BITS}")
endif()

