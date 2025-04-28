cmake_minimum_required(VERSION 3.10)

# Set the project name
project(COBD2PP)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# Find muparser system-wide
find_package(muparser REQUIRED)

# Add source files
add_executable(COBD2PP src/main.cpp)

# Tell CMake where obd-cxx headers are
target_include_directories(COBD2PP PRIVATE
    /usr/local/include/obd-cxx
)

# Tell CMake where obd-cxx library is
target_link_directories(COBD2PP PRIVATE
    /usr/local/lib
)

# Link against muparser and obd-cxx
target_link_libraries(COBD2PP
    muparser
    obd-cxx
)
