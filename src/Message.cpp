#include "Message.hpp"


Query::Query() : read_only_(true) {}
Query::Query(bool r) : read_only_(r) {}

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
