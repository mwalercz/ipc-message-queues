#include "Element.hpp"

#include <stdexcept>
#include <iostream>

bool Element::fulfills(const Comparison lhs, const Comparison rhs) {
    // no 1s where 0s are
    // and at least one 1 in common
    return  !(lhs & (~rhs)) && (lhs & lhs);
}

Element::Element(int value) :
    type_(Type::kInt), int_value_(new int(value)),
    float_value_(nullptr), string_value_(nullptr) {}

Element::Element(float value) :
    type_(Type::kFloat), int_value_(nullptr),
    float_value_(new float(value)), string_value_(nullptr) {}

Element::Element(const std::string& value) :
    type_(Type::kString), int_value_(nullptr),
    float_value_(nullptr), string_value_(new std::string(value)) {}

void Element::swap(const Element& other) {
    type_ = other.getType();
    switch(other.getType()) {
        case kInt: {
            int_value_ = new int(*other.getInt());
            float_value_ = nullptr;
            string_value_ = nullptr;
            break;
        }
        case kFloat: {
            int_value_ = nullptr;
            float_value_ = new float(*other.getFloat());
            string_value_ = nullptr;
            break;
        }
        case kString: {
            int_value_ = nullptr;
            float_value_ = nullptr;
            string_value_ = new std::string(*other.getString());
            break;
        }
    }
}

Element::Element(const Element& other) {
    swap(other);
}

Element::~Element() {
    delete int_value_;
    delete float_value_;
    delete string_value_;
}

Element& Element::operator=(const Element& other) {
    swap(other);
    return *this;
}

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
            float a = *float_value_;
            float b = *other.getFloat();
            if (a == b) return kEqual;
            if (a < b) return kLower;
            return kGreater;
        }
        case kString: {
            std::string a = *string_value_;
            std::string b = *other.getString();
            std::cout << "a: " << a << " b: " << b << std::endl;
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
} std::string* Element::getString() const {
    return string_value_;
}

bool Element::operator==(const Element& other) const {
    return this->compare(other) == kEqual;
}

bool Element::operator!=(const Element& other) const {
    return !(*this == other);
}
