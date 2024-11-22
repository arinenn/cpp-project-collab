cmake_minimum_required(VERSION 3.14)
project(cpp-project-collab)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
# set(CMAKE_CXX_COMPILER ${CPP_COMPILER}) #it's bad...

# add_executable(main main.cpp src/my_add.cpp)
add_executable(test src/test.cpp)

find_package(Python2 COMPONENTS Interpreter NumPy REQUIRED)
include_directories(${Python2_INCLUDE_DIRS})
target_link_libraries(test PRIVATE ${Python2_LIBRARIES} Python2::NumPy)

# find_package(Python3 3.10 COMPONENTS Interpreter NumPy REQUIRED)
# include_directories(${PYTHON_INCLUDE_DIRS})
# target_link_libraries(test ${PYTHON_LIBRARIES} Python3::NumPy)
