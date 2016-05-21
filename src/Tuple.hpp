#ifndef TUPLE_HPP
#define TUPLE_HPP

#include <vector>
#include <map>

#include "Element.hpp"

class Query;
class Tuple {
    public:
        typedef long Type;
        Tuple();
        explicit Tuple(Elements elements);
        bool isMatch(const Query& other) const;
    private:
        static Type calculateType(const Elements& elements);
        Type type_;
        Elements elements_;
};

class TupleMap {
    public:
        void remove(const Query& query);
        Tuple find(const Query& query);
        Tuple fetch(const Query& query);
    private:
        std::map<Tuple::Type, Tuple> tuples_;
        // last iterator maybe ?

};

#endif /* TUPLE_HPP */
