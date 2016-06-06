#include "PendingQueries.hpp"
#include <algorithm>

bool PrioQueue::remove(const Tuple& value){
    auto it = std::find_if(this->c.begin(), this->c.end(), [&](const Query& q){
            return value.isMatch(q);
            });
    // auto it = std::find(this->c.begin(), this->c.end(), value);
    if (it != this->c.end()) {
        this->c.erase(it);
        std::make_heap(this->c.begin(), this->c.end(), this->comp);
        return true;
    }
    else {
        return false;
    }
}

Time PendingQueries::getNextTimeout() const {
    if (queries_.empty()) {
        return 0; // there is no pending queries
    } else {
        return queries_.top().getLeftTimeout();
    }
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

bool PendingQueries::remove(const Tuple& t){
    return queries_.remove(t);
}
