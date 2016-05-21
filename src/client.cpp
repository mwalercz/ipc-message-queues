#include "Queue.hpp"
#include <iostream>


int main() {
  Queue q(1234);
  q.init();
  q.send("Litwo, ojczyzno moja...");
  std::cout << q.clientRcv() << std::endl;
  q.close();
}

