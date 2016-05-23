#include "TupleMap.hpp"

#include <algorithm>
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

std::unique_ptr<Tuple> TupleMap::fetch(const Query& query) {
    TypeMap::iterator type_it = type_map_.find(query.getType());
    if (type_it != type_map_.end()) {
        Tuples& tuples = type_it->second;
        for (auto tuple_it = tuples.begin(); tuple_it != tuples.end();
             ++tuple_it) {
            if (tuple_it->isMatch(query)) {
                std::unique_ptr<Tuple> result(new Tuple(*tuple_it));
                tuples.erase(tuple_it);
                if (tuples.empty()) {
                    type_map_.erase(type_it);  // XXX WARNING: it invalidates
                                               // tuple_it, so be carefull not
                                               // to use tuple_it after it
                }
                return result;
            }
        }
    }
    return nullptr;
}
