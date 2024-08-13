cmake_minimum_required(VERSION 3.28.3)
project(MatrixLib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(inc)

set(SOURCES
    src/Matrix.cpp
    src/ConfigReader.cpp
    src/LibSetup.cpp
)

# For SWIG
find_package(SWIG REQUIRED)
find_package(Python3 REQUIRED COMPONENTS Development)

include(UseSWIG)

set(SWIG_INTERFACE swig/Matrix.i)

# Set the SWIG flags to use C++ mode and include directories
set_property(SOURCE ${SWIG_INTERFACE} PROPERTY CPLUSPLUS ON)
set_property(SOURCE ${SWIG_INTERFACE} PROPERTY INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/inc)

swig_add_library(MatrixLib
    LANGUAGE python
    SOURCES ${SWIG_INTERFACE} ${SOURCES}
    OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}"
)

target_link_libraries(MatrixLib Python3::Python)

# Ensure the generated SWIG files are treated as C++
set_property(TARGET MatrixLib PROPERTY SWIG_USE_TARGET_INCLUDE_DIRECTORIES TRUE)

# Copy config.ini to the build and python directories
add_custom_command(
    TARGET MatrixLib POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/config.ini
        ${CMAKE_BINARY_DIR}/config.ini
    COMMENT "Copying config.ini to the build directory"
)

add_custom_command(
    TARGET MatrixLib POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/config.ini
        ${CMAKE_SOURCE_DIR}/python/config.ini
    COMMENT "Copying config.ini to the python directory"
)