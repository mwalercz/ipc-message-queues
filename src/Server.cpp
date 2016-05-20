#include "Server.hpp"

Server::Server() {
    //FIXME
}

Server::~Server() {
    //FIXME
}

// FIXME
void Server::serve() {
    /* while (1) {
        pending_queries_.removeTimedoutQueries();  // i.a. sends wakeup msgs to authors
        timeout = pending_queries_.getNextTimeout();  // shortest timeout in pending queries
        msg_part = queue_in_.recv(timeout);  // block if nothing in the queue
        if (!msg_part) {  // woke up by timer
            continue;
        }
        //FIXME
        process_msg_part(msg_part);
        if (any_msg_complete()) {
            UnqPtr<Message> parsed_msg = parser_.parse(getCompletedMessage());
            if (parsed_msg.isExpired()) {
                queue_out_.sendWakeupMsg(parsed_msg.getPid());
            }
            switch (parsed_msg->getType()) {
                case Message::Type::Query: {
                        UnqPtr<Query> query = cast_non_poly<Query, Message>(std::move(parsed_msg));
                        handleQuery(*query);
                        break;
                    }
                case Message::Type::Output: {
                        UnqPtr<Output> output = cast_non_poly<Output, Message>(std::move(parsed_msg));
                        handleOutput(*output);
                        break;
                    }
                case Message::Type::Invalid: {
                        // TODO
                        // panic ?
                        break;
                    }
                default:
                    break;
            }
        }
    } */
}

void Server::handleQuery(const Query& query) {
    Tuple result;
    try {
        result = tuples_.find(query);
    }
    catch (...) { // FIXME
        addToPendingQueries(query);
        return;
    }
    if (query.isReadOnly()) {
        tuples_.remove(query);
    }
    // FIXME
    // queue_out_.send(query.getPid(), result);
}

void Server::handleOutput(const Output& output) {
    // //FIXME
    // //remove timed out queries and try to match pending query
    // found = iter_over_pending_queries(insert);
    // if(found){
        // queue_out_.send(parsed_msg);
    // }
    // else {
        // output(parsed_msg);
    // }
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

