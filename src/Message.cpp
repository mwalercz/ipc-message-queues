#include "Message.hpp"

Length QueryPart::getIdx() const {
    return idx_;
}


Query::QueryParts Query::getParts() const {
    return parts_;
}

bool QueryPart::isMatch(const Element& element) const {
    return reference_point_.compare(element) == expected_;
}
