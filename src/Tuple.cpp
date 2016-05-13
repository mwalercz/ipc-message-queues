#include "Tuple.hpp"

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
