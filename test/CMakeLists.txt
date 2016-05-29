# set(CMAKE_CXX_STANDARD 11)

find_package (Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
include_directories (${Queues_SOURCE_DIR}/src
                     ${Boost_INCLUDE_DIRS}
                     )
add_definitions (-DBOOST_TEST_DYN_LINK)
add_executable (TestElement test_element.cpp)
add_executable (TestTuple test_tuple.cpp)
add_executable (TestTupleMap test_tuple_map.cpp)


add_library(test_links INTERFACE)
add_executable(Test test.cpp )
target_link_libraries(Test
        QueuesServ
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        )
add_executable(TestParser test_parser.cpp ../src/HelperFuns.hpp)
target_link_libraries(TestParser
        Parser
        QueuesServ
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        )

target_link_libraries(test_links
                      INTERFACE
                      QueuesServ
                      ${Boost_FILESYSTEM_LIBRARY}
                      ${Boost_SYSTEM_LIBRARY}
                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                      )

target_link_libraries (TestElement test_links)
target_link_libraries (TestTuple test_links)
target_link_libraries (TestTupleMap test_links)
add_test (NAME TestElement COMMAND TestElement)
add_test (NAME TestTuple COMMAND TestTuple)
add_test (NAME TestTupleMap COMMAND TestTupleMap)

add_test(NAME MyTest COMMAND Test)
add_test(NAME MyTest2 COMMAND TestParser)
