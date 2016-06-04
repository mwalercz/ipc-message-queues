#define BOOST_TEST_MODULE LindaClientTests
#include <boost/test/unit_test.hpp>

//using python object model:
#define private public

#include "Queue.hpp"
#include "LindaClient.hpp"
#include <fstream>

BOOST_AUTO_TEST_CASE(LindaClientRead) {
  std::ofstream file;
  file.open("./test_keys");
  file << 1234 << " " << 1235;
  file.close();
  
  Queue qIn(1234);
  qIn.init();
  Queue qOut(1235);
  qOut.init();
  LindaClient client("./test_keys");

  //initialize timeval
  timeval tv;
  tv.tv_sec=0;
  tv.tv_usec = 0;

  std::string query = "THERE BE QUERIES";
  //Put dummy server response into in queue
  qIn.clientSend("Dummy response", 0);
  client.read(query,tv);

  //check what will server receive
  
  std::string testStr =  qOut.clientRcv();
  // std::cout << q.clientRcv() << std::endl;

  //cleanup
  qIn.close();
  qOut.close();
  BOOST_CHECK_EQUAL("read "+query,testStr);
}

BOOST_AUTO_TEST_CASE(LindaClientInput) {
  std::ofstream file;
  file.open("./test_keys");
  file << 1234 << " " << 1235;
  file.close();
  
  Queue qIn(1234);
  qIn.init();
  Queue qOut(1235);
  qOut.init();
  LindaClient client("./test_keys");

  //initialize timeval
  timeval tv;
  tv.tv_sec=0;
  tv.tv_usec = 0;

  std::string query = "THERE BE QUERIES";
  //Put dummy server response into in queue
  qIn.clientSend("Dummy response", 0);
  client.input(query,tv);

  //check what will server receive
  
  std::string testStr =  qOut.clientRcv();
  // std::cout << q.clientRcv() << std::endl;

  //cleanup
  qIn.close();
  qOut.close();
  BOOST_CHECK_EQUAL("input "+query,testStr);
}

BOOST_AUTO_TEST_CASE(LindaClientOutput) {
  std::ofstream file;
  file.open("./test_keys");
  file << 1234 << " " << 1235;
  file.close();
  
  Queue qIn(1234);
  qIn.init();
  Queue qOut(1235);
  qOut.init();
  LindaClient client("./test_keys");

  //initialize timeval
  timeval tv;
  tv.tv_sec=0;
  tv.tv_usec = 0;

  std::string query = "THERE BE QUERIES";
  //Put dummy server response into in queue
  qIn.clientSend("Dummy response", 0);
  client.output(query);

  //check what will server receive
  Queue::MsgHeader msg = qOut.clientRcvHeader();
  std::string testStr = qOut.clientRcvBody(msg.size);
  // std::cout << q.clientRcv() << std::endl;

  //cleanup
  qIn.close();
  qOut.close();
  BOOST_CHECK_EQUAL("output "+query,testStr);
}

BOOST_AUTO_TEST_CASE(LindaClientTimeout) {
  std::ofstream file;
  file.open("./test_keys");
  file << 1234 << " " << 1235;
  file.close();
  
  Queue qIn(1234);
  qIn.init();
  Queue qOut(1235);
  qOut.init();
  LindaClient client("./test_keys");

  //initialize timeval
  timeval tv;
  tv.tv_sec=0;
  tv.tv_usec = 0;

  std::string query = "THERE BE QUERIES";
  //Put dummy server response into in queue
  qIn.clientSend("Dummy response", Queue::TIMEOUT);

  //check what will client receive (timeout)
  std::string testStr =  client.input(query,tv);


  
  qOut.clientRcv();
  // std::cout << q.clientRcv() << std::endl;

  //cleanup
  qIn.close();
  qOut.close();
  BOOST_CHECK_EQUAL(Queue::errorMessages[Queue::TIMEOUT],testStr);
}

BOOST_AUTO_TEST_CASE(LindaClientParse) {
  std::ofstream file;
  file.open("./test_keys");
  file << 1234 << " " << 1235;
  file.close();
  
  Queue qIn(1234);
  qIn.init();
  Queue qOut(1235);
  qOut.init();
  LindaClient client("./test_keys");

  //initialize timeval
  timeval tv;
  tv.tv_sec=0;
  tv.tv_usec = 0;

  std::string query = "THERE BE QUERIES";
  //Put dummy server response into in queue
  qIn.clientSend("Dummy response", Queue::PARSE);
  
  std::string testStr =  client.input(query,tv);
  
  qOut.clientRcv();
  // std::cout << q.clientRcv() << std::endl;

  //cleanup
  qIn.close();
  qOut.close();
  BOOST_CHECK_EQUAL(Queue::errorMessages[Queue::PARSE],testStr);
}
