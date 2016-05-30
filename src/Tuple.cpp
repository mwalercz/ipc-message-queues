#include "Tuple.hpp"

#include <stdexcept>
#include <string>
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
    for (int i=0; i<elements_.size(); ++i) {
        if (elements_[i] != other.elements_.at(i))
            return false;
    }
    return true;
}



void Tuple::swap(const Tuple &other) {
    type_ = other.getType();
    for (auto element : other.elements_){
        elements_.push_back(element);
    }

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











