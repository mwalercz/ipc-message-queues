#include "Queue.hpp"

#include <cstring>
#include <ctime>
#include <iostream>
#include <stdexcept>

#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

#include <errno.h>
#include <string.h>

void Queue::connect() {
  pid = getpid();
  int msgflg = 0666;
  if((msqid = msgget(key, msgflg)) < 0) {
    throw std::runtime_error("ERROR: Can't connect to queue -- " + std::string(strerror(errno)));
  }
}

void Queue::sendHeader(pid_t pid, int size, int time, int timeout) {
  MsgHeader msg;
  msg.mtype = pid;
  msg.size = size;
  msg.time = time;
  msg.timeout = timeout;
  int ret = msgsnd(msqid,&msg,msgHeaderSize,0);
  if(ret==-1)
    throw std::runtime_error("ERROR: Can't send header -- " + std::string(strerror(errno)));
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

  int ret = msgsnd(msqid,msg,str.size()+1,0);
  free(msg);
  if(ret==-1)
    throw std::runtime_error("ERROR: Can't send message body -- " + std::string(strerror(errno)));
}

Queue::MsgHeader Queue::clientRcvHeader() {
  MsgHeader msg;
  int ret = msgrcv(msqid, &msg, msgHeaderSize, pid, 0);
  if(ret==-1)
    throw std::runtime_error("ERROR: Can't receive header -- " + std::string(strerror(errno)));
  return msg;
}

std::string Queue::clientRcvBody(int size) {
  MsgBody *msg = reinterpret_cast<MsgBody*>(malloc(sizeof(MsgBody)+size));

  int ret = msgrcv(msqid,msg,size,pid,0);
  std::string str(msg->body);
  free(msg);
  if(ret==-1)
    throw std::runtime_error("ERROR: Can't receive body -- " + std::string(strerror(errno)));
  return str;
}

std::string Queue::clientRcv() {
  MsgHeader msg = clientRcvHeader();
  if(msg.timeout==0)
    return clientRcvBody(msg.size);
  else if(msg.timeout<=errorMessages.size())
    return errorMessages[msg.timeout];
  else
    throw std::runtime_error("ERROR: Wrong timeout value from server: " + std::to_string(msg.timeout));
}


const std::vector<std::string> Queue::errorMessages = {
  "NONE", //never used
  "TIMEOUT", //1
  "PARSE ERROR", //2
  "OK" //3
};

