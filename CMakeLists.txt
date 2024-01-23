cmake_minimum_required(VERSION 3.5)

project(linear_algebra LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include_directories("include")

add_library(linear_algebra)

target_sources(linear_algebra PRIVATE   ${CMAKE_CURRENT_SOURCE_DIR}/include/matrix.hpp
                                        ${CMAKE_CURRENT_SOURCE_DIR}/include/vector.hpp

                                        ${CMAKE_CURRENT_SOURCE_DIR}/src/matrix.cpp
                                        ${CMAKE_CURRENT_SOURCE_DIR}/src/vector.cpp)

target_include_directories(linear_algebra
    INTERFACE include/
)
