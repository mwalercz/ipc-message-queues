#include "Element.hpp"
#include <stdexcept>

Element::Element(float *float_value) {
    float_value_ = float_value;
    type_ = Type::Float;
}

Element::Element(int *int_value) {
    int_value_ = int_value;
    type_ = Type::Int;
}

Element::Element(std::string *string_value) {
    string_value_ = string_value;
    type_ = Type::String;
}

//Element::Element(Element &el) {
//    string_value_ = el.string_value_;
//    float_value_ = el.float_value_;
//    string_value_ = el.string_value_;
//    type_ = el.type_;
//}

//void Element::setFloat(float *float_value) {
//    float_value_ = float_value;
//    type_ = Type::Float;
//}
//
//void Element::setInt(int *int_value) {
//    int_value_ = int_value;
//    type_ = Type::Int;
//}
//
//void Element::setString(std::string *string_value) {
//    string_value_ = string_value;
//    type_ = Type::String;
//}

Element::Comparison Element::compare(const Element &other) const {
    if (other.getType() != this->type_) {
        throw std::domain_error("Can't compare elements with different types");
    }
    switch (type_) {
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

int *Element::getInt() const {
    return int_value_;
}

float *Element::getFloat() const {
    return float_value_;
}

std::string *Element::getString() const {
    return string_value_;
}
