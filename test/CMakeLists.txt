# set(CMAKE_CXX_STANDARD 11)

find_package (Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
include_directories (${Queues_SOURCE_DIR}/src
                     ${Boost_INCLUDE_DIRS}
                     )
add_definitions (-DBOOST_TEST_DYN_LINK)

add_executable (TestElement test_element.cpp)
add_executable (TestTuple test_tuple.cpp)
add_executable (TestTupleMap test_tuple_map.cpp)
add_executable (TestLindaClient test_linda_client.cpp)
add_executable (TestParser test_parser.cpp)
add_executable (TestServerSink test_server_sink.cpp)
add_executable (TestServer test_server.cpp)

add_library(test_links INTERFACE)
target_link_libraries (TestParser
        Parser
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        )
target_link_libraries (TestLindaClient
        LindaClient
        QueuesServ
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        )

target_link_libraries (test_links
        INTERFACE
        QueuesServ
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        )

target_link_libraries (TestServer
        QueuesServ
        Parser
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        )

target_link_libraries (TestElement test_links)
target_link_libraries (TestTuple test_links)
target_link_libraries (TestTupleMap test_links)
target_link_libraries (TestLindaClient test_links)
target_link_libraries (TestServerSink test_links)


add_test (NAME TestElement COMMAND TestElement)
add_test (NAME TestTuple COMMAND TestTuple)
add_test (NAME TestTupleMap COMMAND TestTupleMap)
add_test (NAME TestParser COMMAND TestParser)
add_test (NAME TestLindaClient COMMAND TestLindaClient)
add_test (NAME TestServerSink COMMAND TestServerSink)
add_test (NAME TestServer COMMAND TestServer)
