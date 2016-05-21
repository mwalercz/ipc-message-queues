#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <string>
#include <vector>

class Element {
    public:
        enum Type {
            Int,
            Float,
            String
        };
        enum Comparison {
            kLower,
            kLowerOrEqual,
            kEqual,
            kGreaterOrEqual,
            kGreater,
        };
        Element(int value);
        Element(float value);
        Element(const std::string& value);
        ~Element();
        Comparison compare(const Element& other) const;
        Type getType() const;
        int* getInt() const;
        float* getFloat() const;
        std::string* getString() const;
    private:
        Type type_;
        int* int_value_;
        float* float_value_;
        std::string* string_value_;
};

typedef std::vector<Element> Elements;

#endif /* ELEMENT_HPP */
