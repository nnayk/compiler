#include "NewArrayExpression.hpp"

namespace ast {

// Constructor
NewArrayExpression::NewArrayExpression(int lineNum, const std::string& size)
    : AbstractExpression(lineNum), size(size) {}

// Getter method for size
const std::string& NewArrayExpression::getSize() const {
    return size;
}

} // namespace ast

