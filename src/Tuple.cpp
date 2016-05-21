#include "Tuple.hpp"
#include "Message.hpp"

#include <stdexcept>
#include <string>

Tuple::Tuple(Elements elements) : elements_(elements) {
    type_ = calculateType(elements);
}

Tuple::Tuple() {}

bool Tuple::isMatch(const Query& query) const {
    Query::QueryParts parts = query.getParts();
    for (auto p : parts) {
        Length idx = p.getIdx();
        if (! p.isMatch(elements_.at(idx)) ) {
            return false;
        }
    }
    return true;
}

Tuple::Type Tuple::calculateType(const Elements& elements) {
    if (elements.size() > 32) {
        throw std::domain_error("Element size must be lower or equal 32. (" +
                                std::to_string(elements.size()) + ")");
    }
    Type types = 0;
    for (auto element : elements) {
        switch (element.getType()) {
            case Element::Type::Int:
                types |= 1;
                break;
            case Element::Type::Float:
                types |= 2;
                break;
            case Element::Type::String:
                types |= 3;
                break;
            default:
                //FIXME
                // throw up;
                break;
        }
        types <<= 2;
    }
    types >>= 2;
    return types;
}
