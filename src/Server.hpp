#ifndef SERVER_HPP
#define SERVER_HPP

#include <memory>

#include "Element.hpp"
#include "TupleMap.hpp"
#include "Message.hpp"
#include "PendingQueries.hpp"
#include "ServerSink.hpp"
#include "./parser/Parser.h"
#include "Queue.hpp"

template <typename T>
using UnqPtr = std::unique_ptr<T>;

class Server : MessageVisitor {
public:
    Server(const std::string& keys_filename);
    virtual ~Server() = default;
    virtual void visit(Output& output);
    virtual void visit(Query& query);

    void serve();

    static void sigint_handler(int signo);

    static volatile sig_atomic_t running;
private:
    void handleQuery(const Query& query);
    void handleOutput(const Output& output);
    static key_t getKey(int proj_id);
    static void save_keys(const std::string& filename, key_t in, key_t out);

    PendingQueries pending_queries_;
    UnqPtr<ServerSink> queue_out_;
    UnqPtr<ServerSink> queue_in_;
    TupleMap tuples_;
    Parser parser_;
};

template <typename T, typename S>
UnqPtr<T> cast_poly(UnqPtr<S> basePointer);


template <typename T, typename S>
inline UnqPtr<T> cast_non_poly(UnqPtr<S> basePointer);

#endif  // SERVER_HPP
