#include "DotExpression.hpp"

namespace ast {

// Constructor
DotExpression::DotExpression(int lineNum, std::shared_ptr<Expression> left, const std::string& id)
    : AbstractExpression(lineNum), left_(left), id_(id) {}

// Getter for left expression
std::shared_ptr<Expression> DotExpression::getLeft() const {
    return left_;
}

// Getter for id
const std::string& DotExpression::getId() const {
    return id_;
}

} // namespace ast

