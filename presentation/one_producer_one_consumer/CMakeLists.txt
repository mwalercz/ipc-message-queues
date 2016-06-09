add_executable(t1_consumer consumer.cpp)
add_executable(t1_producer producer.cpp)

target_link_libraries(t1_consumer LindaClient)
target_link_libraries(t1_producer LindaClient)
