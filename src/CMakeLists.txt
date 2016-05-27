# set(CMAKE_CXX_STANDARD 11)


add_library(QueuesClient
            Queue.cpp Queue.hpp
           )

add_library(QueuesServ
            Server.cpp Server.hpp
            Element.cpp Element.hpp
            Tuple.cpp Tuple.hpp
            TupleMap.cpp TupleMap.hpp
            Message.cpp Message.hpp
            PendingQueries.cpp PendingQueries.hpp
            Queue.cpp Queue.hpp
           )

add_executable(asd main.cpp)
add_executable(client client.cpp)

target_link_libraries(asd QueuesServ)

add_subdirectory(parser)
target_link_libraries(client QueuesClient)
