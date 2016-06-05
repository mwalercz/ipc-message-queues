#define BOOST_TEST_MODULE ServerSinkTest
#include <boost/test/unit_test.hpp>

#include <memory>
#include <string>
#include <vector>

#include "Element.hpp"
#include "PendingQueries.hpp"
#include "Queue.hpp"

#define private public
#define protected public

#include "ServerSink.hpp"

BOOST_AUTO_TEST_SUITE(test_server_sink)

BOOST_AUTO_TEST_CASE(ServerSinkRecv) {
    PendingQueries pending;
    pending.add({303, 0, 5, 0x00, true});
    ServerSink s(1234, pending);
    s.init();

    std::vector<std::string> expected = {"test0", "test1", "test2", "test3"};

    pid_t pid = 1;
    for (auto e : expected) {
        s.send(pid, e, 0);
        pid = (pid+1) & 0x3 + 1; // (pid + 1) % 4 + 1
    }

    std::vector<std::string> output;
    std::unique_ptr<std::string> msg;
    while((msg = s.recv())) {
        output.push_back(*msg.release());
    }
    s.close();

    BOOST_CHECK_EQUAL_COLLECTIONS(output.begin(), output.end(),
                                  expected.begin(), expected.end());
}

BOOST_AUTO_TEST_SUITE_END()
