#include "LvalueDot.hpp"

namespace ast {

// Constructor
LvalueDot::LvalueDot(int lineNum, std::shared_ptr<Lvalue> left, const std::string& id)
    : lineNum(lineNum), left(left), id(id) {}

// Getter methods
int LvalueDot::getLineNum() const {
    return lineNum;
}

std::shared_ptr<Lvalue> LvalueDot::getLeft() const {
    return left;
}

std::string LvalueDot::getId() const {
    return id;
}

std::shared_ptr<Type> LvalueDot::resolveType(Env &env) const {
    //TODO: implement
    return std::make_shared<NullType>();
}

} // namespace ast

