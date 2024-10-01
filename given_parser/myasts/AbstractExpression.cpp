#include "AbstractExpression.hpp"

namespace ast {

// Constructor definition
AbstractExpression::AbstractExpression(int lineNum) : lineNum(lineNum) {}

// Getter for lineNum
int AbstractExpression::getLineNum() const {
    return lineNum;
}

}  // namespace ast