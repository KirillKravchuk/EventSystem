cmake_minimum_required(VERSION 3.16)

project(EventSystem LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
    message(STATUS "Building for Windows")
elseif (UNIX)
    message(STATUS "Building for Linux")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)

add_subdirectory (Test_task)