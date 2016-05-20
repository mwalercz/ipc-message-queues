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
