#include "Queue.hpp"
#include <iostream>
#include <stdexcept>
#include <unistd.h>
#include <ctime>
#include <cstring>


void Queue::init() {
  pid = getpid();
  int msgflg = IPC_CREAT | 0666;
  if((msqid = msgget(key, msgflg)) < 0)
    throw std::runtime_error("Can't open queue");
}

void Queue::close() {
  msgctl( msqid, IPC_RMID, 0);
}


void Queue::sendHeader(pid_t pid, int size, int time, int timeout) {
  MsgHeader msg;
  msg.mtype = pid;
  msg.header[0] = size;
  msg.header[1] = time;
  msg.header[2] = timeout;
  msgsnd(msqid,&msg,msgHeaderSize,0);
}


void Queue::send(pid_t pid, const std::string &str) {
  sendHeader(pid,
	     str.size()+1, //null terminated string
	     time(0),
	     timeout);
  //Send body
  MsgBody msg;
  msg.mtype = pid;
  char buf[size+sizeof(long)];

  msg = (MsgBody*)buf;

  std::strcpy(msg.body, str.c_str());

  msgsnd(msqid,&msg,str.size()+1,0);
}

Queue::MsgHeader Queue::clientRcvHeader() {
  MsgHeader msg;
  msgrcv(msqid,&msg,msgHeaderSize,pid,0);
  return msg;
}

std::string Queue::clientRcvBody(int size) {
  MsgBody msg;
  
  msgrcv(msqid,&msg,size,pid,0);
  std::string str(msg.body);
  return str;
}

std::string Queue::clientRcv() {
  MsgHeader msg = clientRcvHeader();
  //TODO: Timeout messsage handling
  return clientRcvBody(msg.header[0]);
}
