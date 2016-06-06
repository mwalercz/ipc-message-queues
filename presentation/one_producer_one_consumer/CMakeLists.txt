add_executable(consumer consumer.cpp)
add_executable(producer producer.cpp)

target_link_libraries(consumer LindaClient)
target_link_libraries(producer LindaClient)
