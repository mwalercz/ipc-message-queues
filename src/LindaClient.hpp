#ifndef LINDA_CLIENT_HPP
#define LINDA_CLIENT_HPP
#include "Queue.hpp"
#include <string>
#include <fstream>

class LindaClient {
private:
  Queue* queueIn;
  Queue* queueOut;

  void init(const std::string& path) {
    std::ifstream file;
    file.open(path);
    int inKey, outKey;
    file >> inKey;
    file >> outKey;
    file.close();
    queueIn = new Queue(inKey);
    queueOut = new Queue(outKey);
    queueIn->connect();
    queueOut->connect();
      
  }

  std::string sendAndRcv(const std::string&  prefix, const std::string& query, timeval tv) {
    queueOut->clientSend(prefix + query, tv.tv_sec*1000+tv.tv_usec/1000);
    return queueIn->clientRcv();
  }
public:
  LindaClient(const std::string& path) {init(path);}
  ~LindaClient() {delete queueIn; delete queueOut;}

  std::string input(const std::string& query, timeval tv) {
    return sendAndRcv("input ", query, tv);
  }
  std::string read(const std::string& query, timeval tv) {
    return sendAndRcv("read ", query, tv);
  }
  std::string output(const std::string& query) {
    queueOut->clientSend("output " + query, Queue::timeout);
    return queueIn->clientRcv();
  }
  
};

#endif
