#ifndef SERVER_HPP
#define SERVER_HPP

#include <memory>

#include "Element.hpp"
#include "Tuple.hpp"
#include "Message.hpp"
// TODO
// * Queue class
// * storing unfinished messages
// * getting last message
//
template <typename T>
using UnqPtr = std::unique_ptr<T>;

class Server : MessageVisitor {
public:
    Server();
    virtual ~Server();
    virtual void visit(Output& output);
    virtual void visit(Query& query);

    void serve();
private:
    UnqPtr<Message> getCompletedMessage();
    void handleQuery(const Query& query);
    void handleOutput(const Output& output);
    void addToPendingQueries(const Query& query);


    // FIXME
    // Parser parser_;
    // Queue queue_out_;
    // Queue queue_in_;
    TupleMap tuples_;

};

template <typename T, typename S>
UnqPtr<T> cast_poly(UnqPtr<S> basePointer);


template <typename T, typename S>
inline UnqPtr<T> cast_non_poly(UnqPtr<S> basePointer);

#endif  // SERVER_HPP
