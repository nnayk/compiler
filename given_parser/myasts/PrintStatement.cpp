#include "PrintStatement.hpp"

namespace ast {

// Constructor initializes the base class and sets the expression
PrintStatement::PrintStatement(int lineNum, std::shared_ptr<Expression> expression, bool newLine)
    : AbstractStatement(lineNum), expression(expression), newLine(newLine) {}
void PrintStatement::typecheck(Env &env) {
}
} // namespace ast

