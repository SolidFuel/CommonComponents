cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(CommonComponents VERSION 0.1.0)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

#Compile commands, useful for some IDEs like VS-Code
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

if (CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    set(default_build_type "Release")
    if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
        STRING "Choose the type of build." FORCE)
    endif()
endif()


if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    #static linking in Windows
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    add_compile_options("$<$<CONFIG:Release>:/O2>")
endif()

add_compile_definitions("$<$<CONFIG:Release>:SF_DEBUG=0>")

#---------------------------
#----------------------------

set(JUCE_ENABLE_MODULE_SOURCE_GROUPS 1)

find_package(juce REQUIRED)

juce_add_module(solidfuel)