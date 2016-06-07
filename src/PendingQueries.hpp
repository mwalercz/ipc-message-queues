#ifndef PENDING_QUERIES_HPP
#define PENDING_QUERIES_HPP

#include <queue>
#include <functional>
#include "Message.hpp"

class PrioQueue : public std::priority_queue<Query, std::vector<Query>> {
    public:
        bool remove(const Tuple& value);
};

class PendingQueries {
    public:
        typedef PrioQueue Queries;
        std::vector<MsgPid> removeTimedoutQueries();
        Time getNextTimeout() const;
        void add(const Query& q);
        bool remove(const Tuple& t);
    private:
        Queries queries_;
};

#endif /* PENDING_QUERIES_HPP */
