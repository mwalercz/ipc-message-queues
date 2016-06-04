#include "Tuple.hpp"

#include <stdexcept>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <memory>

#include "Message.hpp"

Tuple::Tuple(Elements elements) : elements_(elements) {
    type_ = calculateType(elements);
}

bool Tuple::isMatch(const Query& query) const {
    if (getType() != query.getType())
        return false;
    Query::QueryParts parts = query.getParts();
    for (auto p : parts) {
        Length idx = p.getIdx();
        if (! p.isMatch(elements_.at(idx)) ) {
            return false;
        }
    }
    return true;
}

Tuple::Type Tuple::getType() const {
    return type_;
}

Tuple::Type Tuple::calculateType(const Elements& elements) {
    if (elements.size() > 32) {
        throw std::domain_error("Element size must be lower or equal 32. (" +
                                std::to_string(elements.size()) + ")");
    }
    Type types = 0;
    for (auto element : elements) {
        types <<= 2;
        switch (element.getType()) {
            case Element::Type::kInt:
                types |= 1;
                break;
            case Element::Type::kFloat:
                types |= 2;
                break;
            case Element::Type::kString:
                types |= 3;
                break;
        }
    }
    return types;
}

bool Tuple::operator==(const Tuple& other) const {
    if (type_ != other.getType())
        return false;
    for (unsigned i=0; i<elements_.size(); ++i) {
        if (elements_[i] != other.elements_.at(i))
            return false;
    }
    return true;
}

std::string Tuple::toString() const {
    std::stringstream ss;
    ss << "(" << std::fixed; // << std::setprecision(std::numeric_limits<long double>::digits10);
    for (auto i : elements_) {
        switch(i.getType()) {
            case Element::Type::kInt: {
                 ss << *(i.getInt()) << ",";
                break;
            }
            case Element::Type::kFloat: {
                std::cout << *(i.getFloat()) << std::endl;
                 ss << *(i.getFloat()) << ",";
                break;
            }
            case Element::Type::kString: {
                 ss << "\"" << *(i.getString()) << "\"" << ",";
                break;
            }
        }
    }
    std::string tmp = ss.str();
    tmp.pop_back();
    std::stringstream output;
    output << tmp << ")";
    return output.str();
}

void TypeCalculator::calculate(const Element &element) {
    if (current_idx > 31){
        throw std::domain_error("Elements size must be lower or equal 32");
    }
    type_ <<= 2;
    switch (element.getType()) {
        case Element::Type::kInt:
            type_ |= 1;
            break;
        case Element::Type::kFloat:
            type_ |= 2;
            break;
        case Element::Type::kString:
            type_ |= 3;
            break;
    }
    current_idx += 1;
}

Tuple::Type TypeCalculator::getType() {
    return type_;
}

void TypeCalculator::reset() {
    type_ = 0;
    current_idx = 0;
}

TypeCalculator::TypeCalculator() : type_(0), current_idx(0){}
