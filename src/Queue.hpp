#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string>


class Queue{
private:
  const static int timeout = 500; //ms?
  const static int msgHeaderSize = 3*sizeof(int); 
  const static int msgBodySize = 1024;
  
  struct MsgHeader {
    long mtype;
    int header[3]; //0 - size,1 - time,2 - timeout
  };
  struct MsgBody {
    long mtype;
    char body[msgBodySize];
  };
    
    
  //Message queue id
  int msqid;
  key_t key;
  pid_t pid;

  void sendHeader(pid_t pid, int size, int time, int timeout);
  MsgHeader clientRcvHeader();
  std::string clientRcvBody(int size);
  
public:
  Queue(key_t _key) : key(_key) {}
  void init();

  //Destroys queue, run only on server exit!
  void close();


  void send(pid_t pid, const std::string &str);
  void send(const std::string &str) {send(pid,str);}
  
  void sendTimeoutInfo(pid_t pid) {
    sendHeader(pid,0,time(0),1); //timeout = 1
  }

  std::string clientRcv();

  //TODO: Server receive -- Maciek K.?
};

#endif
