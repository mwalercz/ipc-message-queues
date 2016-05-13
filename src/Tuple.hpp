#ifndef TUPLE_HPP
#define TUPLE_HPP
#include "Message.hpp"
#include "Element.hpp"
#include <vector>

class Tuple {
public:
    Tuple(long type, Elements elements) : type_(type), elements_(elements) {};
    bool isMatch(Query& query) {
        Query::QueryParts parts = query.getParts();
        //tutaj jeszcze nalezy dodac sytuacje jesli w query jest part typu obojętny, np int:*
        for (auto p : parts) {
            Length idx = p.getIdx();
            if (! p.isMatch(elements_.at(idx)) ) {
                return false;
            }
        }
        return true;
    }
private:
    long type_;
    Elements elements_;
};

#endif /* ifndef TUPLE_HPP */
