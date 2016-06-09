#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <string>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <vector>

class Queue{
public:
  struct MsgHeader {
    long mtype;
    int size;
    int time;
    unsigned timeout;
  };
protected:
  static const int msgHeaderSize = 2*sizeof(int)+sizeof(unsigned);


  struct MsgBody {
    long mtype;
    char body[0];
  };

  void sendHeader(pid_t pid, int size, int time, unsigned timeout);

  //Message queue id
  int msqid;
  key_t key;
  pid_t pid;


private:
  MsgHeader clientRcvHeader();
  std::string clientRcvBody(int size);

public:
  static const std::vector<std::string> errorMessages;
  const static int timeout = 500; //ms?
  enum Error {
    kNone=0,
    kTimeout=1,
    kParseError=2,
    kOk=3
  };

  Queue(key_t _key) : key(_key), msqid(-1) {}
  virtual ~Queue() = default;

  //Connects to queue (client)
  void connect();

  void send(pid_t pid, const std::string &str, unsigned timeout=0);

  void clientSend(const std::string &str,unsigned timeout=timeout) {send(pid,str,timeout);}

  void sendErrorInfo(pid_t pid, Error err) {
    sendHeader(pid,0,time(0),err);
  }

  std::string clientRcv();
};

#endif
