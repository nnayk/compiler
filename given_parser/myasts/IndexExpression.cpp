#include "IndexExpression.hpp"

namespace ast {

// Constructor
IndexExpression::IndexExpression(int lineNum, std::shared_ptr<Expression> left, std::shared_ptr<Expression> index)
    : AbstractExpression(lineNum), left(left), index(index) {}

// Getter for left expression
std::shared_ptr<Expression> IndexExpression::getLeft() const {
    return left;
}

// Getter for index expression
std::shared_ptr<Expression> IndexExpression::getIndex() const {
    return index;
}

} // namespace ast

