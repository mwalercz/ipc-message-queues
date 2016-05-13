#ifndef ELEMENT_HPP
#define ELEMENT_HPP value
#include <string>
#include <vector>

class Element {
    public:
        enum Type {
            kInt,
            kFloat,
            kString
        };
        enum Comparison {
            kNone, // jesli mamy sytuacje Query int:* 
            kLower,
            kLowerOrEqual,
            kEqual,
            kGreaterOrEqual,
            kGreater,
        };
        Comparison compare(const Element& other);
    private:
        Type type_;
        int* int_value_;
        float* float_value_;
        std::string* string_value_;
};

typedef std::vector<Element> Elements;
#endif /* ifndef ELEMENT_HPP */
