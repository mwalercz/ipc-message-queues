cmake_minimum_required(VERSION 3.1)
project(PRESENTATION)
set(CMAKE_CXX_STANDARD 11)

set(SRC ../src)
include_directories(BEFORE ${SRC})

add_library(LindaClient
        ${SRC}/LindaClient.hpp
        ${SRC}/Queue.cpp
        ${SRC}/Queue.hpp
        )

add_subdirectory(one_producer_one_consumer)
add_subdirectory(one_producer_more_consumers)