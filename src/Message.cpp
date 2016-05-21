#include "Message.hpp"

#include "Element.hpp"
#include "Tuple.hpp"

Output::Output(const Tuple& tuple) : tuple_(tuple) {}

void Output::accept(MessageVisitor& v) {
}

Tuple Output::getTuple() const{
    return tuple_;
}


Query::Query() : read_only_(true) {}
Query::Query(bool r) : read_only_(r) {}

void Query::accept(MessageVisitor& v) {
    v.visit(*this);
}

bool Query::isReadOnly() const {
    return read_only_;
}


Length QueryPart::getIdx() const {
    return idx_;
}

Query::QueryParts Query::getParts() const {
    return parts_;
}

bool QueryPart::isMatch(const Element& element) const {
    return reference_point_.compare(element) == expected_;
}

Time Message::getEstimatedTimeout() const {
    // we are cheating a bit in here
    // for more info check https://stackoverflow.com/questions/1859201/add-seconds-to-a-date
    return  send_time_ + timeout_;
}

bool Message::compareTimes(Time l, Time r) const {
    double diff = std::difftime(l, r);
    if (diff >= 0 ) {
        return true;
    }
    return false;
}

TimeDuration Message::getLeftTimeout() const {
    return std::difftime(getEstimatedTimeout(), time(NULL));
}

bool Message::isExpired() const {
    return compareTimes(getEstimatedTimeout(), time(NULL));
}

bool operator<(const Message& lhs, const Message& rhs) {
    return lhs.compareTimes(rhs.getEstimatedTimeout(), lhs.getEstimatedTimeout());
}
