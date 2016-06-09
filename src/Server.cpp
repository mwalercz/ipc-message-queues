#include "Server.hpp"

#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <fstream>
#include <iostream>

#include <sys/types.h>
#include <sys/ipc.h>
#include <signal.h>

#include "Element.hpp"
#include "Message.hpp"
#include "./parser/Parser.h"
#include "ServerSink.hpp"

volatile sig_atomic_t Server::running = 1;
void Server::sigint_handler(int signo) {
    Server::running = 0;
}

Server::Server(const std::string& keys_filename)
    : pending_queries_() {
    key_t key_in = getKey(0);
    key_t key_out = getKey(1);
    queue_in_ = std::move(UnqPtr<ServerSink>(new ServerSink(key_in, pending_queries_)));
    queue_out_ = std::move(UnqPtr<ServerSink>(new ServerSink(key_out, pending_queries_)));
    save_keys(keys_filename, key_in, key_out);
    signal(SIGINT, Server::sigint_handler);
}

void Server::serve() {
     while (running) {
         std::cout << "*" << std::endl;
         std::vector<MsgPid> timeouted = pending_queries_.removeTimedoutQueries();
         for (auto pid : timeouted) {
            std::cout << "[TIMEOUT] Removing timeouted query. Owner's PID: " << pid << std::endl;
            queue_out_->sendTimeout(pid);
         }
         std::unique_ptr<std::pair<Queue::MsgHeader, std::string>> raw_data;
         std::cout << "Receiving data...";
         std::cout.flush();
         raw_data = queue_in_->recv();
         std::cout << "done."  << std::endl;
         if (raw_data) {
             Queue::MsgHeader header = raw_data->first;
             std::string raw_string = raw_data->second;
             try {
                 std::unique_ptr<Message> msg =
                     parser_.parse(raw_string, header.time, header.timeout,
                                   static_cast<unsigned>(header.mtype));
                 msg->accept(*this);
             } catch (std::domain_error& e) {
                queue_out_->sendParseError(header.mtype);
                std::cout << "[PARSE_ERROR] Parse errorm. Owner's PID: " << header.mtype << std::endl;
             }
         }
     }
}

void Server::visit(Output& output) {
    std::cout << "[OUTPUT] Handling output. Owner's PID: " << output.getPid() << std::endl;
    handleOutput(output);
}

void Server::visit(Query& query) {
    std::cout << "[QUERY] Handling query. Owner's PID: " << query.getPid() << std::endl;
    handleQuery(query);
}

void Server::handleQuery(const Query& query) {
    std::unique_ptr<Tuple> result;
    if (query.isReadOnly()) {
        result = tuples_.find(query);
    } else {
        result = tuples_.fetch(query);
    }

    if (result) {
        queue_out_->send(query.getPid(), result->toString());
    } else {
        pending_queries_.add(query);
    }
}

void Server::handleOutput(const Output& output) {
    UnqPtr<Query> query = pending_queries_.remove(output.getTuple());
    if (query) {
        queue_out_->send(query->getPid(), output.getTuple().toString());
    }
    else {
        tuples_.insert(output.getTuple());
    }
    queue_out_->sendWakeup(output.getPid());
}

key_t Server::getKey(int proj_id) {
    key_t key = ftok(".", proj_id);
    if (key < 0) {
        throw std::runtime_error("Failed to get new key: " +
                                 std::to_string(errno));
    }
    return key;
}

void Server::save_keys(const std::string& filename, key_t in, key_t out) {
    std::ofstream ofs(filename);
    ofs << in << " " << out << std::endl;
}

template <typename T, typename S>
UnqPtr<T> cast_poly(UnqPtr<S> basePointer) {
    T *tmp = dynamic_cast<T*>(basePointer.get());
    UnqPtr<T> derivedPointer;
    if(tmp != nullptr) {
        basePointer.release();
        derivedPointer.reset(tmp);
    }
}

template <typename T, typename S>
inline UnqPtr<T> cast_non_poly(UnqPtr<S> basePointer) {
    UnqPtr<T> derived(static_cast<T*>(basePointer.release()));
    return derived;
}
