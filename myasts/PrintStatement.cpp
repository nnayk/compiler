#include "PrintStatement.hpp"

namespace ast {

// Constructor initializes the base class and sets the expression
PrintStatement::PrintStatement(int lineNum, Expression* expression)
    : AbstractStatement(lineNum), expression(expression) {}

} // namespace ast

