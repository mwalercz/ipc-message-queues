#include "Message.hpp"
#include "Element.hpp"
#include "Tuple.hpp"

Message::Message(MsgPid pid, Time send_time, TimeDuration timeout,
                 Tuple::Type type)
    : pid_(pid),
      send_time_(send_time),
      timeout_(timeout),
      type_(type) {}

Time Message::getEstimatedTimeout() const {
    // we are cheating a bit in here
    // for more info check https://stackoverflow.com/questions/1859201/add-seconds-to-a-date
    return  send_time_ + timeout_;
}

bool Message::compareTimes(Time l, Time r) const {
    double diff = std::difftime(l, r);
    if (diff < 0 ) {
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

MsgPid Message::getPid() const {
    return pid_;
}

Tuple::Type Message::getType() const {
    return type_;
}

bool operator<(const Message& lhs, const Message& rhs) {
    return lhs.compareTimes(rhs.getEstimatedTimeout(), lhs.getEstimatedTimeout());
}

Output::Output(const Tuple& tuple, MsgPid pid, Time send_time,
               TimeDuration timeout)
    : Message(pid, send_time, timeout, tuple.getType()), tuple_(tuple) {}

void Output::accept(MessageVisitor& v) {
    v.visit(*this);
}

Tuple Output::getTuple() const{
    return tuple_;
}

Query::Query(MsgPid pid, Time send_time, TimeDuration timeout, Tuple::Type type,
             QueryParts parts, bool read_only)
    : Message(pid, send_time, timeout, type), parts_(parts), read_only_(read_only) {}

Query::Query(MsgPid pid, Time send_time, TimeDuration timeout, Tuple::Type type, bool read_only)
    : Message(pid, send_time, timeout, type), read_only_(read_only) {}


void Query::accept(MessageVisitor& v) {
    v.visit(*this);
}

bool Query::isReadOnly() const {
    return read_only_;
}

void Query::appendPart(const QueryPart& q) {
    parts_.push_back(q);
}

Query::QueryParts Query::getParts() const {
    return parts_;
}

QueryPart::QueryPart(Length idx, const Element& reference_point,
    Element::Comparison expected) : idx_(idx),
    reference_point_(reference_point), expected_(expected) {}

Length QueryPart::getIdx() const {
    return idx_;
}

bool QueryPart::isMatch(const Element& element) const {
    return Element::fulfills(element.compare(reference_point_), expected_);
}

Element QueryPart::getElement() const {
    return reference_point_;
}


