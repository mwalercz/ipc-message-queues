#define BOOST_TEST_MODULE ServerTest

#include <boost/test/unit_test.hpp>
#include <boost/utility/binary.hpp>

#include <memory>

#define private public

#include "../src/Server.hpp"


BOOST_AUTO_TEST_SUITE(test_server)

BOOST_AUTO_TEST_CASE( TestServerServe ) {
   Server server("srv_test_keys");
   server.serve();
}

BOOST_AUTO_TEST_SUITE_END()
