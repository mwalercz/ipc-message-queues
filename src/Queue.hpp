#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <string>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <vector>

class Queue{
protected:
  static const int msgHeaderSize = 3*sizeof(int);

  struct MsgHeader {
    long mtype;
    int size;
    int time;
    int timeout;
  };

  struct MsgBody {
    long mtype;
    char body[0];
  };

  void sendHeader(pid_t pid, int size, int time, int timeout);

  //Message queue id
  int msqid;
  key_t key;
  pid_t pid;


private:
  static const std::vector<std::string> errorMessages;

  MsgHeader clientRcvHeader();
  std::string clientRcvBody(int size);

public:
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

  void send(pid_t pid, const std::string &str, int timeout=0);

  void clientSend(const std::string &str,int timeout=timeout) {send(pid,str,timeout);}

  void sendErrorInfo(pid_t pid, Error err) {
    sendHeader(pid,0,time(0),err);
  }

  std::string clientRcv();
};

#endif
