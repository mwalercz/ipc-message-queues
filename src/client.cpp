#include "Queue.hpp"
#include <iostream>
#include <unistd.h>

int main() {
  Queue q(1234);
  q.init();
  q.send(getpid(),"\
Litwo, ojczyzno moja, ty jestes jak zdrowie \
ile Cie trzeba cenic, ten tylko sie dowie, \
kto Cie stracil",0);
  q.send(getpid(),"Abc",200);
  std::cout << q.clientRcv() << std::endl;
  std::cout << q.clientRcv() << std::endl;
  q.close();
}

