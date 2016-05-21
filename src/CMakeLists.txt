# set(CMAKE_CXX_STANDARD 11)


add_library(QueuesServ Server.cpp Server.hpp)
add_library(QueuesQueue Queue.cpp Queue.hpp)
add_library(QueuesServ
            Server.cpp Server.hpp
            Element.cpp Element.hpp
            Tuple.cpp Tuple.hpp
            Message.cpp Message.hpp
            PendingQueries.cpp PendingQueries.hpp
           )
>>>>>>> e98a127ae02e0ff20eec4b744d1d12e004b0c913
add_executable(asd main.cpp)
add_executable(client client.cpp)
target_link_libraries(asd QueuesServ)
target_link_libraries(client QueuesQueue)
