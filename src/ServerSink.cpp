#include "ServerSink.hpp"

#include <iostream>

#include <cstring>
#include <ctime>
#include <iostream>
#include <memory>
#include <stdexcept>

#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <signal.h>

#include "Queue.hpp"
#include "PendingQueries.hpp"

volatile sig_atomic_t ServerSink::got_alarm_interrupt = 0;

void ServerSink::sig_alarm_handler(int signo) {
    got_alarm_interrupt = 1;
}

ServerSink::ServerSink(key_t key, const PendingQueries& pending_queries)
    : Queue(key), pending_queries_(pending_queries) {
    init();
    std::cout << "WHATEVER!" << std::endl;
    // set up SIGALRM handler
    signal(SIGALRM, ServerSink::sig_alarm_handler);
}

ServerSink::~ServerSink() {
    if(msqid != -1) close();
}

std::unique_ptr<std::pair<Queue::MsgHeader, std::string>> ServerSink::recv() {
    for (auto header = headers_.begin(); header != headers_.end(); ++header) {
        std::unique_ptr<std::string> body(rcvBody(header->mtype, header->size));
        if(body) {
            std::unique_ptr<std::pair<Queue::MsgHeader, std::string>> res(
                new std::pair<Queue::MsgHeader, std::string>(*header, *body));
            headers_.erase(header);
            return res;
        }
    }
    std::unique_ptr<MsgHeader> new_header(
        rcvHeader(pending_queries_.getNextTimeout()));
    if (new_header) {
        headers_.push_back(*new_header.release());
    }
    return nullptr;
}

void ServerSink::send(pid_t pid, const std::string& msg) {
}

void ServerSink::sendWakeup(pid_t pid) {
}

void ServerSink::sendTimeout(pid_t pid) {
}

void ServerSink::init() {
  pid = getpid();
  int msgflg = IPC_CREAT | 0666;
  if((msqid = msgget(key, msgflg)) < 0) {
    throw std::runtime_error("ERROR: Can't open queue");
  }
  std::cout << "Init - key: " << key << " msqid: " << msqid << std::endl;
}

void ServerSink::close() {
  msgctl( msqid, IPC_RMID, 0);
}


std::unique_ptr<Queue::MsgHeader> ServerSink::rcvHeader(unsigned timeout) {
    std::unique_ptr<MsgHeader> header(new MsgHeader);
    alarm(timeout);
    ssize_t res = msgrcv(msqid, header.get(), msgHeaderSize, 0, 0);
    int err = errno;
    alarm(0); // cancel panding alarms
    if ( res != Queue::msgHeaderSize ) {
        if((err == EINTR) && got_alarm_interrupt) {
            header = nullptr;
        } else {
            throw std::runtime_error("Failed to receive header: " +
                                     std::to_string(err));
        }
    }
    got_alarm_interrupt = 0;
    return header;
}

std::unique_ptr<std::string> ServerSink::rcvBody(pid_t pid, int size) {
    std::unique_ptr<std::string> out;
    MsgBody *msg_body = reinterpret_cast<MsgBody*>(malloc(sizeof(MsgBody)+size));
    ssize_t res = msgrcv(msqid, msg_body, size, pid, IPC_NOWAIT);
    int err = errno;
    if ( res != size ) {
        free(msg_body);
        if(err == ENOMSG) { // no message of disired type
            out = nullptr;
        } else {
            throw std::runtime_error("Failed to receive body: " +
                                     std::to_string(err));
        }
    } else {
        out = std::unique_ptr<std::string>(new std::string(msg_body->body));
        free(msg_body);
    }
    return out;
}
