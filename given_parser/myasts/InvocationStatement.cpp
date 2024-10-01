#include "InvocationStatement.hpp"

namespace ast {

// Constructor
InvocationStatement::InvocationStatement(int lineNum, std::shared_ptr<Expression> expression)
    : AbstractStatement(lineNum), expression(expression) {}

// Getter for the expression
std::shared_ptr<Expression> InvocationStatement::getExpression() const {
    return expression;
}

} // namespace ast

