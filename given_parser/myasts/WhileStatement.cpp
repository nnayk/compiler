#include "WhileStatement.hpp"

namespace ast {

WhileStatement::WhileStatement(int lineNum, std::shared_ptr<Expression> guard, std::shared_ptr<Statement> body)
    : AbstractStatement(lineNum), guard(guard), body(body) {}

void WhileStatement::typecheck(Env &env) {
}

} // namespace ast

