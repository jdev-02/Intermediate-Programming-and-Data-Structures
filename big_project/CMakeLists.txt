cmake_minimum_required(VERSION 3.10)

project(BigProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Find libcurl
find_package(CURL REQUIRED)
if(CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "libcurl not found")
endif()

# Add source files
set(SOURCES
    src/this_is_a_test.cpp
)

# Create executable
add_executable(test_app ${SOURCES})

# Link libcurl
target_link_libraries(test_app ${CURL_LIBRARIES})

# Enable warnings and debug info
target_compile_options(test_app PRIVATE -Wall -g)

# Add test executable
enable_testing()
find_package(GTest REQUIRED)