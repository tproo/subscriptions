cmake_minimum_required(VERSION 3.23)
project(subscriptions)

#include_directories(src)
add_subdirectory(src)

option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(tests)
endif()

