add_library(LindaClient
            Queue.cpp Queue.hpp
            LindaClient.hpp
           )

add_library(QueuesServ
            Server.cpp Server.hpp
            Element.cpp Element.hpp
            Tuple.cpp Tuple.hpp
            TupleMap.cpp TupleMap.hpp
            Message.cpp Message.hpp
            PendingQueries.cpp PendingQueries.hpp
            Queue.cpp Queue.hpp
            ServerSink.cpp ServerSink.hpp
            Server.cpp Server.hpp
           )

add_executable(asd main.cpp)
add_executable(client client.cpp)
add_executable(server_service server_service.cpp)

target_link_libraries(asd QueuesServ)
target_link_libraries(client LindaClient)
target_link_libraries(server_service QueuesServ Parser)

add_subdirectory(parser)
