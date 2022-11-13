cmake_minimum_required(VERSION 3.23)
project(subscriptions)

set(CMAKE_CXX_STANDARD 17)

set(INCLUDES ./includes)

set(HEADERS
        ${INCLUDES}/function.h
        ${INCLUDES}/holder.h includes/broadcaster.h)

add_library(subscriptions STATIC ${HEADERS})
set_target_properties(subscriptions PROPERTIES LINKER_LANGUAGE CXX)
