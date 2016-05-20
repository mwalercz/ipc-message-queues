#include "PendingQueries.hpp"

Time PendingQueries::getNextTimeout() const {
    return queries_.top().getLeftTimeout();
}

void PendingQueries::add(const Query& q) {
    queries_.push(q);
}

void PendingQueries::removeTimedoutQueries() {
    while(!queries_.empty() && queries_.top().isExpired()){
        Query q = queries_.top();
        queries_.pop();
        // FIXME send information about timed out query ?
    }
}
