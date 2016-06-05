#include "ServerSink.hpp"

#include <cstring>
#include <ctime>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <unistd.h>

#include "Queue.hpp"
#include "PendingQueries.hpp"

std::unique_ptr<std::string> ServerSink::recv() {
    for (auto header : headers_) {
        std::unique_ptr<MsgBody> msg_body(rcvBody(header.mtype, header.size));
        if(msg_body) {
            return std::unique_ptr<std::string> (new std::string(msg_body->body));
        }
    }
    std::unique_ptr<MsgHeader> new_header(
        rcvHeader(pending_queries_.getNextTimeout()));
    if (new_header) {
        headers_.push_back(*new_header.release());
    }
    return nullptr;
}

std::unique_ptr<Queue::MsgHeader> ServerSink::rcvHeader(unsigned timeout) {
    // TODO
    return nullptr;
}

std::unique_ptr<Queue::MsgBody> ServerSink::rcvBody(pid_t pid, int size) {
    // TODO
    return nullptr;
}


