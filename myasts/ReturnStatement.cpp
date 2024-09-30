#include "ReturnStatement.hpp"

namespace ast {

// Constructor that calls the base class constructor
ReturnStatement::ReturnStatement(int lineNum, Expression* expression)
    : AbstractStatement(lineNum), expression(expression) {}

} // namespace ast

