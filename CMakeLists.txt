cmake_minimum_required(VERSION 3.14)
project(fft-heston-cpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXECUTABLE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE EXAMPLE_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/examples/*.cpp)

# Build static library from the source files
add_library(fft-heston-cpp STATIC ${SOURCE_FILES})

# Include headers and other libraries
target_include_directories(fft-heston-cpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Get compilated files for export
set_target_properties(fft-heston-cpp PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# CMake instructions to build examples using the static lib
foreach(EXAMPLE_SOURCE_FILE ${EXAMPLE_SOURCE_FILES})
    get_filename_component(EXAMPLE_NAME ${EXAMPLE_SOURCE_FILE} NAME_WE)
    add_executable(${EXAMPLE_NAME} ${EXAMPLE_SOURCE_FILE})
    target_link_libraries(${EXAMPLE_NAME} PRIVATE fft-heston-cpp)
endforeach()
