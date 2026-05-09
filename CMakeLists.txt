cmake_minimum_required(VERSION 3.10)

project(LinearAlgebra)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

# Source files
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/test.cc)

add_executable(runit ${SOURCES})