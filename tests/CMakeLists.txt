cmake_minimum_required(VERSION 3.23)
project(subscriptions_test)

add_subdirectory("${PROJECT_SOURCE_DIR}/../googletest" "googletest")

include_directories("${PROJECT_SOURCE_DIR}/../src")

add_executable(subscriptions_test first_test.cpp)
target_link_libraries(subscriptions_test gtest gtest_main)
target_link_libraries(subscriptions_test subscriptions)
