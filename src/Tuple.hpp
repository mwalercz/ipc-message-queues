#ifndef TUPLE_HPP
#define TUPLE_HPP

#include <vector>
#include <map>
#include <memory>

#include "Element.hpp"

class Query;
class Tuple {
    public:
        typedef long Type;
        Tuple() = default;
        explicit Tuple(Elements elements);
        bool isMatch(const Query& other) const;
        Type getType() const;

        bool operator==(const Tuple& other) const;

    private:
        static Type calculateType(const Elements& elements);
        Type type_;
        Elements elements_;
};

class TypeCalculator{
    public:
        TypeCalculator();
        typedef long Type;
        void calculate(const Element& element);
        Type getType();
        void reset();

    private:
        Type type_;
        int current_idx;
};
#endif /* TUPLE_HPP */
