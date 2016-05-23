#include "Queue.hpp"
#include <iostream>
#include <stdexcept>
#include <unistd.h>
#include <ctime>
#include <cstring>


void Queue::init() {
  pid = getpid();
  int msgflg = IPC_CREAT | 0666;
  if((msqid = msgget(key, msgflg)) < 0) {
    throw std::runtime_error("ERROR: Can't open queue");
  }
}

void Queue::close() {
  msgctl( msqid, IPC_RMID, 0);
}


void Queue::sendHeader(pid_t pid, int size, int time, int timeout) {
  MsgHeader msg;
  msg.mtype = pid;
  msg.size = size;
  msg.time = time;
  msg.timeout = timeout;
  msgsnd(msqid,&msg,msgHeaderSize,0);
}


void Queue::send(pid_t pid, const std::string &str, int timeout) {
  int msgSize = str.size() + 1; //null terminated C string (+1)
  sendHeader(pid,
	     msgSize,
	     time(0),
	     timeout);
  //Send body
  MsgBody *msg = reinterpret_cast<MsgBody*>(malloc(sizeof(MsgBody)+msgSize));
  msg->mtype = pid;
  std::strcpy(msg->body, str.c_str());

  msgsnd(msqid,msg,str.size()+1,0);
  free(msg);
}

Queue::MsgHeader Queue::clientRcvHeader() {
  MsgHeader msg;
  msgrcv(msqid,&msg,msgHeaderSize,pid,0);
  return msg;
}

std::string Queue::clientRcvBody(int size) {
  MsgBody *msg = reinterpret_cast<MsgBody*>(malloc(sizeof(MsgBody)+size));

  msgrcv(msqid,msg,size,pid,0);
  std::string str(msg->body);
  free(msg);
  return str;
}

std::string Queue::clientRcv() {
  MsgHeader msg = clientRcvHeader();
  if(msg.timeout==0)
    return clientRcvBody(msg.size);
  else if(msg.timeout==1)
    return "TIMEOUT";
  else
    throw std::runtime_error("ERROR: Wrong timeout value from server: (should be 0 or 1)");
}
