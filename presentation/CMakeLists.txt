cmake_minimum_required(VERSION 3.1)
project(PRESENTATION)
set(CMAKE_CXX_STANDARD 11)

set(SRC ../src)
include_directories(BEFORE ${SRC})

add_library(LindaClient
        ${SRC}/LindaClient.hpp
        ${SRC}/Queue.cpp
        ${SRC}/Queue.hpp
        constants.hpp
        )

# add_library(Parser
        # ${SRC}/parser/Scanner.cpp
        # ${SRC}/parser/Scanner.ih
        # ${SRC}/parser/Scannerbase.h
        # ${SRC}/parser/Scanner.h
        # ${SRC}/parser/Parser.cpp
        # ${SRC}/parser/Parser.ih
        # ${SRC}/parser/Parserbase.h
        # ${SRC}/parser/Parser.h
        # ${SRC}/Message.hpp
        # ${SRC}/Message.cpp
        # ${SRC}/Element.hpp
        # ${SRC}/Element.cpp
        # ${SRC}/Tuple.cpp
        # ${SRC}/Tuple.hpp
        # )
add_library(Server
        ${SRC}/parser/Scanner.cpp
        ${SRC}/parser/Scanner.ih
        ${SRC}/parser/Scannerbase.h
        ${SRC}/parser/Scanner.h
        ${SRC}/parser/Parser.cpp
        ${SRC}/parser/Parser.ih
        ${SRC}/parser/Parserbase.h
        ${SRC}/parser/Parser.h
        ${SRC}/Server.hpp
        ${SRC}/Server.cpp
        ${SRC}/Element.cpp
        ${SRC}/Element.hpp
        ${SRC}/Tuple.cpp
        ${SRC}/Tuple.hpp
        ${SRC}/TupleMap.cpp
        ${SRC}/TupleMap.hpp
        ${SRC}/Message.cpp
        ${SRC}/Message.hpp
        ${SRC}/PendingQueries.cpp
        ${SRC}/PendingQueries.hpp
        ${SRC}/Queue.cpp
        ${SRC}/Queue.hpp
        ${SRC}/ServerSink.cpp
        ${SRC}/ServerSink.hpp
        ${SRC}/Server.cpp
        ${SRC}/Server.hpp
        constants.hpp
        )

add_subdirectory(one_producer_one_consumer)
add_subdirectory(one_producer_more_consumers)
add_subdirectory(two_producers_two_consumers_massive)
