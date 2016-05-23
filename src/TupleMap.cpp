#include "TupleMap.hpp"

#include <stdexcept>
#include <string>
#include <memory>

#include "Tuple.hpp"
#include "Message.hpp"

void TupleMap::insert(const Tuple& tuple) {
    Tuple::Type type = tuple.getType();
    TypeMap::iterator it = type_map_.find(type);
    if (it != type_map_.end()) {
        //  there are already tuples of the same type
        it->second.push_back(tuple);
    } else {
        // it's the first tuple of the type
        type_map_.emplace(type, Tuples({tuple}));
    }
}

std::unique_ptr<Tuple> TupleMap::find(const Query& query) const {
    TypeMap::const_iterator it = type_map_.find(query.getType());
    if (it != type_map_.cend()) {
        for (auto tuple : it->second) {
           if (tuple.isMatch(query)) {
               return std::unique_ptr<Tuple>(new Tuple(tuple));
           }
        }
    }
    return nullptr;
}

std::unique_ptr<Tuple> fetch(const Query& query) {
    // TODO
    return nullptr;
}
