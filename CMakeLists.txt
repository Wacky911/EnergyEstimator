cmake_minimum_required(VERSION 3.10)
project(EnergyEstimator)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(${CMAKE_SOURCE_DIR})

# Find Python3
find_package(Python3 REQUIRED COMPONENTS Development NumPy)

include_directories(${Python3_INCLUDE_DIRS} ${Python3_NumPy_INCLUDE_DIRS})

# Source files
set(SOURCES
    src/main.cpp
    src/csv_generator.cpp
    src/csv_read.cpp
    src/energy_estimate.cpp
    src/linear_interpolation.cpp
    src/plot.cpp
)

# Header files (for IDEs and inclusion)
set(HEADERS
    src/csv_generator.hpp
    src/csv_read.hpp
    src/energy_estimate.hpp
    src/linear_interpolation.hpp
    src/matplotlibcpp.h
    src/plot.hpp
)

# Executable
add_executable(EnergyEstimator ${SOURCES} ${HEADERS})

# Link Python libraries
target_link_libraries(EnergyEstimator PRIVATE ${Python3_LIBRARIES})

# Ignore specific warnings
target_compile_options(EnergyEstimator PRIVATE -Wno-deprecated-declarations -fcolor-diagnostics -fansi-escape-codes)

# Set runtime path
set_target_properties(EnergyEstimator PROPERTIES BUILD_RPATH ${Python3_LIBRARY_DIRS})
