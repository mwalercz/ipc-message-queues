#ifndef TUPLE_MAP_HPP
#define TUPLE_MAP_HPP

#include <vector>
#include <map>
#include <memory>

#include "Tuple.hpp"
#include "Message.hpp"

class TupleMap {
    public:
        typedef std::vector<Tuple> Tuples;
        typedef std::map<Tuple::Type, Tuples> TypeMap;
        TupleMap() = default;
        ~TupleMap() = default;

        void insert(const Tuple& tuple);

        /* Returns pointer to copy of first element matching the query.
         * If there's no matching element returns nullptr
         */
        std::unique_ptr<Tuple> find(const Query& query) const;

        /* Returns pointer to copy of first element matching the query
         * and removes it.
         * If there's no matching element returns nullptr
         */
        std::unique_ptr<Tuple> fetch(const Query& query);

    private:
         TypeMap type_map_;
};

#endif /* TUPLE_MAP_HPP */
