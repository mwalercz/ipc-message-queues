#include "Server.hpp"

#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <fstream>

#include <sys/types.h>
#include <sys/ipc.h>

#include "Element.hpp"
#include "Message.hpp"

Server::Server(std::string& keys_filename)
    : pending_queries_() {
    key_t key_in = getKey(0);
    key_t key_out = getKey(1);
    save_keys(keys_filename, key_in, key_out);
}

void Server::serve() {
     while (1) {
         std::vector<MsgPid> timeouted = pending_queries_.removeTimedoutQueries();
         for (auto pid : timeouted) {
            queue_out_->sendTimeout(pid);
         }
         std::unique_ptr<std::pair<Queue::MsgHeader, std::string>> raw_data;
         raw_data = queue_in_->recv();
         if (raw_data) {
             Queue::MsgHeader header = raw_data->first;
             std::string raw_string = raw_data->second;
             try {
                 std::unique_ptr<Message> msg =
                     parser_.parse(raw_string, header.time, header.timeout,
                                   static_cast<unsigned>(header.mtype));
             } catch (std::runtime_error& e) {
                queue_out_->sendParseError(header.mtype);
             }
         } else {
             throw std::runtime_error("Parser returned nullptr");
         }
    }
}

void Server::visit(Output& output) {
    handleOutput(output);
}

void Server::visit(Query& query) {
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
    /* //FIXME
    UnqPtr<Query> query = pending_queries_.remove(output.getTuple());
    if (query) {
        queue_out_->send(query.getPid(), output.getTuple().toString());
    }
    else {
        tuples_.insert(output.getTuple());
    }
    queue_out_->sendWakeup(output.getPid());
    */
}

key_t getKey(int proj_id) {
    key_t key = ftok(".", proj_id);
    if (key < 0) {
        throw std::runtime_error("Failed to get new key: " +
                                 std::to_string(errno));
    }
    return key;
}

void save_keys(const std::string& filename, key_t in, key_t out) {
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
