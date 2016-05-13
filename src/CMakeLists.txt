# set(CMAKE_CXX_STANDARD 11)

add_library(QueuesServ Server.cpp Server.hpp)
add_executable(asd main.cpp)
target_link_libraries(asd QueuesServ)
