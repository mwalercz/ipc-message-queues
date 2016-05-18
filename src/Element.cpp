#include "Element.hpp"
#include <stdexcept>

Element::Comparison Element::compare(const Element& other) const {
    if (other.getType() != this->type_) {
        throw std::domain_error("Can't compare elements with different types");
    }
    switch(type_) {
        case Int: {
            int a = *int_value_;
            int b = *other.getInt();
            if (a == b) return Equal;
            if (a < b) return Lower;
            return Greater;
        }
        case Float: {
            float a = *int_value_;
            float b = *other.getFloat();
            if (a == b) return Equal;
            if (a < b) return Lower;
            return Greater;
        }
        case String: {
            std::string a = *string_value_;
            std::string b = *other.getString();
            if (a == b) return Equal;
            if (a < b) return Lower;
            return Greater;
        }
    }
}

Element::Type Element::getType() const {
    return type_;
}

int* Element::getInt() const {
    return int_value_;
}

float* Element::getFloat() const {
    return float_value_;
}

std::string* Element::getString() const {
    return string_value_;
}
