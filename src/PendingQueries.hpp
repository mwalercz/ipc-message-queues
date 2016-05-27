#ifndef PENDING_QUERIES_HPP
#define PENDING_QUERIES_HPP

#include <queue>
#include <functional>
#include "Message.hpp"

class PendingQueries {
    public:
        typedef std::priority_queue<Query> Queries;
        void removeTimedoutQueries();
        Time getNextTimeout() const;
        void add(const Query& q);
    private:
        Queries queries_;
};

#endif /* PENDING_QUERIES_HPP */
