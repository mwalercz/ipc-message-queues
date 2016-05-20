# set(CMAKE_CXX_STANDARD 11)

add_library(QueuesServ
            Server.cpp Server.hpp
            Element.cpp Element.hpp
            Tuple.cpp Tuple.hpp
            Message.cpp Message.hpp
            PendingQueries.cpp PendingQueries.hpp
           )
add_executable(asd main.cpp)
target_link_libraries(asd QueuesServ)
