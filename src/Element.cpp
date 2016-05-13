#include "Element.hpp"
#include <stdexcept>

Element::Comparison Element::compare(const Element& other) const {
    if (other.getType() != this->type_) {
        throw std::domain_error("Can't compare elements with different types");
    }
    switch(type_) {
        case kInt: {
            int a = *int_value_;
            int b = *other.getInt();
            if (a == b) return kEqual;
            if (a < b) return kLower;
            return kGreater;
        }
        case kFloat: {
            float a = *int_value_;
            float b = *other.getFloat();
            if (a == b) return kEqual;
            if (a < b) return kLower;
            return kGreater;
        }
        case kString: {
            std::string a = *string_value_;
            std::string b = *other.getString();
            if (a == b) return kEqual;
            if (a < b) return kLower;
            return kGreater;
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
