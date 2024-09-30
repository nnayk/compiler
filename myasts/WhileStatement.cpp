#include "WhileStatement.hpp"

namespace ast {

WhileStatement::WhileStatement(int lineNum, Expression* guard, Statement* body)
    : AbstractStatement(lineNum), guard(guard), body(body) {}

} // namespace ast

