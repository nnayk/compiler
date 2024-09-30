#include "IntegerExpression.hpp"

namespace ast {

// Constructor
IntegerExpression::IntegerExpression(int lineNum, const std::string& value)
    : AbstractExpression(lineNum), value(value) {}

// Getter for the value
std::string IntegerExpression::getValue() const {
    return value;
}

} // namespace ast

