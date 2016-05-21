#include "Element.hpp"
#include <stdexcept>

Element::Element(int value) :
    type_(Type::Int), int_value_(new int(value)),
    float_value_(nullptr), string_value_(nullptr) {}

Element::Element(float value) :
    type_(Type::Float), int_value_(nullptr),
    float_value_(new float(value)), string_value_(nullptr) {}

Element::Element(const std::string& value) :
    type_(Type::String), int_value_(nullptr),
    float_value_(nullptr), string_value_(new std::string(value)) {}

Element::~Element() {
    delete int_value_;
    delete float_value_;
    delete string_value_;
}

Element::Comparison Element::compare(const Element& other) const {
    if (other.getType() != this->type_) {
        throw std::domain_error("Can't compare elements with different types");
    }
    switch(type_) {
        case Int: {
            int a = *int_value_;
            int b = *other.getInt();
            if (a == b) return kEqual;
            if (a < b) return kLower;
            return kGreater;
        }
        case Float: {
            float a = *float_value_;
            float b = *other.getFloat();
            if (a == b) return kEqual;
            if (a < b) return kLower;
            return kGreater;
        }
        case String: {
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
