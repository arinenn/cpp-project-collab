cmake_minimum_required(VERSION 3.14)
project(cpp-project-collab)

add_executable(test test.cpp)

# include Eigen
set(LIBRARIES_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${LIBRARIES_INCLUDE_DIR})

# link Eigen
target_include_directories(test PRIVATE LIBRARIES_INCLUDE_DIR)