#include "PrintLnStatement.hpp"

namespace ast {

// Constructor initializes the base class and sets the expression
PrintLnStatement::PrintLnStatement(int lineNum, Expression* expression)
    : AbstractStatement(lineNum), expression(expression) {}

void typecheck(Env &env) override {
}

} // namespace ast

