cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 11)

# Include directories
include_directories(include)

# Add test executable
enable_testing()
find_package(GTest REQUIRED)

add_executable(runListTests tests/listTest.cpp)
target_link_libraries(runListTests GTest::GTest GTest::Main pthread)
add_test(NAME ListTest COMMAND runListTests)

add_executable(runStackTests tests/stackTest.cpp)
target_link_libraries(runStackTests GTest::GTest GTest::Main pthread)
add_test(NAME StackTest COMMAND runStackTests)

add_executable(runQueueTests tests/queueTest.cpp)
target_link_libraries(runQueueTests GTest::GTest GTest::Main pthread)
add_test(NAME QueueTest COMMAND runQueueTests)