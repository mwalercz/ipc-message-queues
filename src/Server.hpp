#ifndef SERVER_HPP
#define SERVER_HPP
#include "Tuple.hpp"
#include "Message.hpp"
#include <memory>

// TODO
// * Queue class
// * storing unfinished messages
// * getting last message
//
template <typename T>
using UnqPtr = std::unique_ptr<T>;

class Server {
public:
    Server();
    virtual ~Server();
    void serve();
private:
    Message getCompletedMessage();
    void handleQuery(Query query);
    void handleOutput(Output output);
    void addToPendingQueries(Query query);


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
