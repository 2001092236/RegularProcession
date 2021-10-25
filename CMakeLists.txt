#cmake_minimum_required(VERSION 3.20)
#project(untitled6)

#set(CMAKE_CXX_STANDARD 17)

#add_executable(untitled6 main.cpp)
cmake_minimum_required(VERSION 2.6)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link runTests with what we want to test and the GTest and pthread library

include_directories(./)

add_executable(Run ./test.cpp ./regular_adapter.cpp ./sequence_regulars.cpp ./Process_regular_expression.cpp)
target_link_libraries(Run ${GTEST_LIBRARIES} pthread)
