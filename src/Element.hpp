#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <string>
#include <vector>
#include <boost/utility/binary.hpp>

class Element {
    public:
        enum Type {
            kInt,
            kFloat,
            kString
        };
        enum Comparison {
            // values are special masks used to compare comparisions
            kLower =            BOOST_BINARY( 100 ),
            kLowerOrEqual =     BOOST_BINARY( 110 ),
            kEqual =            BOOST_BINARY( 010 ),
            kGreaterOrEqual =   BOOST_BINARY( 011 ),
            kGreater =          BOOST_BINARY( 001 )
        };
        static bool fulfills(const Comparison lhs, const Comparison rhs);

        Element(int value);
        Element(float value);
        Element(const std::string& value);
        Element(const Element& other);
        ~Element();
        Element& operator=(const Element& other);
        /* Compares this against other
         * returns such relation R that (this R other)
         */
        Comparison compare(const Element& other) const;
        Type getType() const;
        int* getInt() const;
        float* getFloat() const;
        std::string* getString() const;
        bool operator==(const Element& other) const;
        bool operator!=(const Element& other) const;
    private:
        void swap(const Element& other);
        Type type_;
        int* int_value_;
        float* float_value_;
        std::string* string_value_;
};

typedef std::vector<Element> Elements;

#endif /* ELEMENT_HPP */
