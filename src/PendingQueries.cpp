#include "PendingQueries.hpp"

#include <algorithm>
#include <memory>

#include "Message.hpp"

std::unique_ptr<Query> PrioQueue::remove(const Tuple& value){
    auto it = std::find_if(this->c.begin(), this->c.end(),
                           [&](const Query& q) { return value.isMatch(q); });
    if (it != this->c.end()) {
        std::unique_ptr<Query> query(new Query(*it));
        this->c.erase(it);
        std::make_heap(this->c.begin(), this->c.end(), this->comp);
        return query;
    }
    else {
        return nullptr;
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

std::vector<MsgPid> PendingQueries::removeTimedoutQueries() {
    std::vector<MsgPid> output;
    while(!queries_.empty() && queries_.top().isExpired()){
        output.push_back(queries_.top().getPid());
        queries_.pop();
    }
    return output;
}

std::unique_ptr<Query> PendingQueries::remove(const Tuple& t){
    return queries_.remove(t);
}
