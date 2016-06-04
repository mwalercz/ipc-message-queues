#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string>
#include <vector>


class Queue{
private:

  

  const static int msgHeaderSize = 3*sizeof(int);
  //const static int msgBodySize = 1024;

  const static std::vector<std::string> errorMessages;
  

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


  //Message queue id
  int msqid;
  key_t key;
  pid_t pid;

  void sendHeader(pid_t pid, int size, int time, int timeout);
  MsgHeader clientRcvHeader();
  std::string clientRcvBody(int size);

public:
  const static int timeout = 500; //ms?
  enum Error {
    NONE=0,
    TIMEOUT=1,
    PARSE=2
  };

  Queue(key_t _key) : key(_key) {}

  //Creates queue (server)
  void init();

  //Connects to queue (client)
  void connect();

  //Destroys queue, run only on server exit!
  void close();


  void send(pid_t pid, const std::string &str, int timeout=0);

  void clientSend(const std::string &str,int timeout=timeout) {send(pid,str,timeout);}

  void sendErrorInfo(pid_t pid, Error err) {
    sendHeader(pid,0,time(0),err);
  }

  std::string clientRcv();
  //TODO: Server receive -- Maciek K.?
};

#endif
