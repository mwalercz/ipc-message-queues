add_executable(consumer_2 consumer.cpp)
add_executable(producer_2 producer.cpp)

target_link_libraries(consumer_2 LindaClient)
target_link_libraries(producer_2 LindaClient)
