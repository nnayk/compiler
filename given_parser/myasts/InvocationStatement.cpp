#include "InvocationStatement.hpp"

namespace ast {

// Constructor
InvocationStatement::InvocationStatement(int lineNum, std::shared_ptr<Expression> expression)
    : AbstractStatement(lineNum), expression(expression) {}

// Getter for the expression
std::shared_ptr<Expression> InvocationStatement::getExpression() const {
    return expression;
}

void InvocationStatement::typecheck(Env &env, Function &f) {
    this->getExpression()->resolveType(env);
}

std::string InvocationStatement::get_llvm() {
    spdlog::debug("inside InvocationStatement::{}\n",__func__);
    std::string llvm = this->getExpression()->get_llvm_init();
    auto expr = this->getExpression();
    llvm += expr->get_llvm();
    return llvm;
}

} // namespace ast

