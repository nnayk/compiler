#include "DeleteStatement.hpp"

namespace ast {

// Constructor
DeleteStatement::DeleteStatement(int lineNum, std::shared_ptr<Expression> expression)
    : AbstractStatement(lineNum), expression_(expression) {}

// Getter for the expression
std::shared_ptr<Expression> DeleteStatement::getExpression() const {
    return expression_;
}

void DeleteStatement::typecheck(Env &env, Function &f) {
}

void DeleteStatement::resolve_def_uses(Bblock &block) {
    spdlog::debug("inside DeleteStatement::{}\n",__func__);
    this->getExpression()->resolve_uses(block);
}

} // namespace ast

