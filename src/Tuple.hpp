#ifndef TUPLE_HPP
#define TUPLE_HPP
#include "Message.hpp"
#include "Element.hpp"
#include <vector>

class Tuple {
    public:
        Tuple(long type, Elements elements) : type_(type), elements_(elements) {};
        bool isMatch(const Query& other) const;
    private:
        long type_;
        Elements elements_;
};

#endif /* ifndef TUPLE_HPP */
