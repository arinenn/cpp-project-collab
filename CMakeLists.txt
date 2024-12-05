cmake_minimum_required(VERSION 3.14)
project(heston-fft-pricing)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add_executable(test
#     test.cpp
#     src/fft.cpp
#     src/european_options.cpp
#     src/heston_model.cpp
#     src/heston_pricing.cpp
# )

add_executable(main
    main.cpp
    src/fft.cpp
    src/european_options.cpp
    src/heston_model.cpp
    src/heston_pricing.cpp
)

include_directories(include)
