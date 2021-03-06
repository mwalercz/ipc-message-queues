#ifndef LINDA_CLIENT_HPP
#define LINDA_CLIENT_HPP

#include <string>
#include <fstream>
#include <memory>

#include "Queue.hpp"

class LindaClient {
private:
  std::unique_ptr<Queue> queueIn;
  std::unique_ptr<Queue> queueOut;

  struct Keys{
        int inKey;
        int outKey;
  };

  Keys readFromFile(const std::string& path){
      std::ifstream file(path);
      file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
      Keys keys;
      file >> keys.outKey;
      file >> keys.inKey;
      return keys;
  }
  void init(const std::string& path) {
    initQueues(readFromFile(path));
  }

  void initQueues(Keys keys){
      queueIn = std::unique_ptr<Queue> (new Queue(keys.inKey));
      queueOut = std::unique_ptr<Queue> (new Queue(keys.outKey));
      queueIn->connect();
      queueOut->connect();
  }

  std::string sendAndRcv(const std::string&  prefix, const std::string& query, unsigned timeout) {
    queueOut->clientSend(prefix + query, timeout);
    return queueIn->clientRcv();
  }


public:
  LindaClient(const std::string& path) {init(path);}

  std::string input(const std::string& query, unsigned timeout) {
    return sendAndRcv("input ", query, timeout);
  }
  std::string read(const std::string& query, unsigned timeout) {
    return sendAndRcv("read ", query, timeout);
  }
  void output(const std::string& tuple) {
    queueOut->clientSend("output " + tuple, Queue::timeout);
    std::string response = queueIn->clientRcv();
    if(response!=Queue::errorMessages[Queue::Error::kOk])
       throw std::runtime_error(response);
  }

};

#endif
