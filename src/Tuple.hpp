#ifndef TUPLE_HPP
#define TUPLE_HPP
#include "Message.hpp"
#include "Element.hpp"
#include <vector>

class Tuple {
    public:
        typedef long Type;
        Tuple();
//        setElements(Elements elements);
        explicit Tuple(Elements elements);
        bool isMatch(const Query& other) const;
    private:
        Type type_;
        Elements elements_;
        Type calculateType(const Elements& elements) const;
};

class TupleMap {
    public:
        void remove(Query query);
        Tuple find(Query query);
    private:
        std::map<Tuple::Type, Tuple> tuples_;
        // last iterator maybe ?

};

#endif /* ifndef TUPLE_HPP */
