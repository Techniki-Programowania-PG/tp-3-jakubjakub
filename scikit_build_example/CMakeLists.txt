cmake_minimum_required(VERSION 3.15)
project(signal_processing)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(extern/pybind11)
add_subdirectory(extern/matplotplusplus)

set(SOURCES
    src/bindings.cpp
    src/generator.cpp
    src/fourier.cpp
    src/filter.cpp  
)

pybind11_add_module(signal_processing ${SOURCES})

target_link_libraries(signal_processing PRIVATE matplot)
target_include_directories(signal_processing PRIVATE extern/matplotplusplus/source)
