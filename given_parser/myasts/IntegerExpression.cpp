#include "IntegerExpression.hpp"

namespace ast {

// Constructor
IntegerExpression::IntegerExpression(int lineNum, const std::string& value)
    : AbstractExpression(lineNum), value(value) {}

// Getter for the value
std::string IntegerExpression::getValue() const {
    return value;
}

std::shared_ptr<Type> IntegerExpression::resolveType(Env &env) {
    return std::make_shared<IntType>();
}

} // namespace ast

