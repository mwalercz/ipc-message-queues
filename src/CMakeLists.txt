# set(CMAKE_CXX_STANDARD 11)

add_library(QueuesServ Server.cpp Server.hpp)
add_library(QueuesQueue Queue.cpp Queue.hpp)
add_executable(asd main.cpp)
add_executable(client client.cpp)
target_link_libraries(asd QueuesServ)
target_link_libraries(client QueuesQueue)
