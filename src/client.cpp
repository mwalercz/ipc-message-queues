#include "Queue.hpp"
#include "LindaClient.hpp"
#include <iostream>
#include <unistd.h>



int main() {
  //initialize queues
  Queue qIn(1234);
  qIn.init();
  Queue qOut(1235);
  qOut.init();
  LindaClient client("./test_keys");

  //initialize timeval
  timeval tv;
  tv.tv_sec=0;
  tv.tv_usec = 0;

  //Put dummy server response into in queue
  qIn.clientSend("Dummy response", Queue::TIMEOUT);
  std::cout << client.input("THERE BE QUERIES",tv) << std::endl;

  //check what will server receive
  std::cout << qOut.clientRcv() << std::endl;
  // std::cout << q.clientRcv() << std::endl;

  //cleanup
  qIn.close();
  qOut.close();
}

