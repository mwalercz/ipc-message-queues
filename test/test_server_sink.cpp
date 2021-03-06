#define BOOST_TEST_MODULE ServerSinkTest
#include <boost/test/unit_test.hpp>

#include <memory>
#include <string>
#include <vector>
#include <cstring>
#include <utility>

#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

#include "Message.hpp"
#include "PendingQueries.hpp"

#define private public
#define protected public

#include "Queue.hpp"
#include "ServerSink.hpp"

BOOST_AUTO_TEST_SUITE(test_server_sink)

BOOST_AUTO_TEST_CASE(ServerSinkRecv_simple) {
    PendingQueries pending;
    pending.add({303, 0, 5, 0x00, true});
    int qkey = ftok(".", 0);
    ServerSink s(qkey, pending);
    Queue client(qkey);
    client.connect();

    std::vector<std::string> expected = {"test0", "1", "testtesttest2", "t3"};

    pid_t pid = 1;
    for (auto e : expected) {
        client.send(pid, e, 1);
        pid = ((pid+1) & 1) + 1;
    }

    std::vector<std::pair<Queue::MsgHeader, std::string>> output;
    std::unique_ptr<std::pair<Queue::MsgHeader, std::string>> msg;
    std::size_t n=expected.size();
    while(n) {
        msg = s.recv();
        if(msg) {
            output.push_back(*msg.release());
            --n;
        }
    }

    BOOST_CHECK_EQUAL(output[0].second, expected[0]);
    BOOST_CHECK_EQUAL(output[1].second, expected[1]);
    BOOST_CHECK_EQUAL(output[2].second, expected[2]);
    BOOST_CHECK_EQUAL(output[3].second, expected[3]);

}

BOOST_AUTO_TEST_CASE(ServerSinkRcv) {
    PendingQueries pending;
    pending.add({303, 0, 5, 0x00, true});
    int qkey = 1234;
    ServerSink s(qkey, pending);
    Queue client(qkey);
    client.connect();

    std::vector<Queue::MsgHeader> expected = {
        {.mtype = 1, .size = 12, .time = 0, .timeout = 3},
        {.mtype = 2, .size = 14, .time = 1, .timeout = 2},
        {.mtype = 3, .size = 16, .time = 2, .timeout = 1},
    };

    const int hs = Queue::msgHeaderSize;
    pid_t pid = 1;
    for (Queue::MsgHeader& header : expected) {
        s.sendHeader(header.mtype, header.size, header.time, header.timeout);
    }

    std::vector<std::unique_ptr<Queue::MsgHeader>> output;
    for (std::size_t i = expected.size(); i--;) {
        output.emplace_back(s.rcvHeader());
    }

    BOOST_REQUIRE(output[0] != nullptr);
    BOOST_CHECK(memcmp(output[0].get(), &expected[0], Queue::msgHeaderSize) == 0);
    BOOST_REQUIRE(output[1] != nullptr);
    BOOST_CHECK(memcmp(output[1].get(), &expected[1], Queue::msgHeaderSize) == 0);
    BOOST_REQUIRE(output[2] != nullptr);
    BOOST_CHECK(memcmp(output[2].get(), &expected[2], Queue::msgHeaderSize) == 0);

}

BOOST_AUTO_TEST_CASE(ServerSinkRcvBody) {
    PendingQueries pending;
    pending.add({303, 0, 5, 0x00, true});
    int qkey = 2021;
    ServerSink s(qkey, pending);
    Queue client(qkey);
    client.connect();

    std::vector<std::string> expected = {
        "qwerty",
        "whateverlonglongenouthtobelonglongandlongertheandendond",
        "a"
    };
    pid_t pid = 1;
    for (auto msg : expected) {
        client.send(pid++, msg, 0);
    }

    std::vector<std::unique_ptr<std::string>> output;
    for (pid_t i = 1; i < pid; ++i) {
        std::unique_ptr<Queue::MsgHeader> h(s.rcvHeader());
        output.emplace_back(s.rcvBody(h->mtype, h->size));
    }

    BOOST_REQUIRE(output[0] != nullptr);
    BOOST_CHECK_EQUAL(*output[0], expected[0]);
    BOOST_REQUIRE(output[1] != nullptr);
    BOOST_CHECK_EQUAL(*output[1], expected[1]);
    BOOST_REQUIRE(output[2] != nullptr);
    BOOST_CHECK_EQUAL(*output[2], expected[2]);
}

BOOST_AUTO_TEST_CASE(ServerSinkSend_simple) {
    PendingQueries pending;
    pending.add({303, 0, 5, 0x00, true});
    int qkey = 2021;
    ServerSink s(qkey, pending);
    Queue client(qkey);
    client.connect();

    pid_t pid = 12;
    std::string msg = "THEFMEUSSCKAINGGE";
    client.pid = pid;
    s.send(pid, msg);

    BOOST_CHECK_EQUAL(client.clientRcv(), msg);
}
BOOST_AUTO_TEST_CASE(ServerSinkSend) {
    PendingQueries pending;
    pending.add({303, 0, 5, 0x00, true});
    int qkey = 2021;
    ServerSink s(qkey, pending);
    Queue client(qkey);
    client.connect();

    std::vector<std::string> expected = {
        "qwerty",
        "whateverlonglongenouthtobelonglongandlongertheandendond",
        "d",
        "d",
    };

    pid_t pid = 1;
    for (auto msg : expected) {
        s.send(pid, msg);
        pid = pid==1 ? 2 : 1;
    }

    std::vector<std::string> received;
    for (auto msg : expected) {
        client.pid=pid;
        pid = pid==1 ? 2 : 1;
        received.emplace_back(client.clientRcv());
    }

    BOOST_CHECK_EQUAL_COLLECTIONS(received.begin(), received.end(),
                                  expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE(ServerSinkSendWakeup) {
    PendingQueries pending;
    pending.add({303, 0, 5, 0x00, true});
    int qkey = 2021;
    ServerSink s(qkey, pending);
    Queue client(qkey);
    client.connect();


    std::vector<std::string> expected = {
        "OK",
        "OK",
        "OK",
        "OK",
        "OK",
    };
    pid_t pid = 1;
    unsigned n[3] = {0xdeadbeef, 0, 0};
    for (auto msg : expected) {
        s.sendWakeup(pid);
        n[pid] += 1;
        pid = ((pid+1) & 1) + 1;
    }

    std::vector<std::string> received;
    client.pid = 1;
    for (unsigned i=n[1]; i--;) {
        received.emplace_back(client.clientRcv());
    }
    client.pid = 2;
    for (unsigned i=n[2]; i--;) {
        received.emplace_back(client.clientRcv());
    }

    BOOST_CHECK_EQUAL_COLLECTIONS(received.begin(), received.end(),
                                  expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE(ServerSinkSendTimeout) {
    PendingQueries pending;
    pending.add({303, 0, 5, 0x00, true});
    int qkey = 2021;
    ServerSink s(qkey, pending);
    Queue client(qkey);
    client.connect();

    std::vector<std::string> expected = {
        "TIMEOUT",
        "TIMEOUT",
        "TIMEOUT",
        "TIMEOUT",
        "TIMEOUT",
    };
    pid_t pid = 1;
    unsigned n[3] = {0xdeadbeef, 0, 0};
    for (auto msg : expected) {
        s.sendTimeout(pid);
        n[pid] += 1;
        pid = ((pid+1) & 1) + 1;
    }

    std::vector<std::string> received;
    client.pid = 1;
    for (unsigned i=n[1]; i--;) {
        received.emplace_back(client.clientRcv());
    }
    client.pid = 2;
    for (unsigned i=n[2]; i--;) {
        received.emplace_back(client.clientRcv());
    }

    BOOST_CHECK_EQUAL_COLLECTIONS(received.begin(), received.end(),
                                  expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE(ServerSinkSendParseError) {
    PendingQueries pending;
    pending.add({303, 0, 5, 0x00, true});
    int qkey = 2021;
    ServerSink s(qkey, pending);
    Queue client(qkey);
    client.connect();


    std::vector<std::string> expected = {
        "PARSE ERROR",
        "PARSE ERROR",
        "PARSE ERROR",
        "PARSE ERROR",
        "PARSE ERROR",
    };
    pid_t pid = 1;
    unsigned n[3] = {0xdeadbeef, 0, 0};
    for (auto msg : expected) {
        s.sendParseError(pid);
        n[pid] += 1;
        pid = ((pid+1) & 1) + 1;
    }

    std::vector<std::string> received;
    client.pid = 1;
    for (unsigned i=n[1]; i--;) {
        received.emplace_back(client.clientRcv());
    }
    client.pid = 2;
    for (unsigned i=n[2]; i--;) {
        received.emplace_back(client.clientRcv());
    }

    BOOST_CHECK_EQUAL_COLLECTIONS(received.begin(), received.end(),
                                  expected.begin(), expected.end());
}

BOOST_AUTO_TEST_SUITE_END()
