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

std::string InvocationStatement::get_llvm(Bblock &block) {
    spdlog::debug("inside InvocationStatement::{}\n",__func__);
    auto expr = this->getExpression();
    std::string llvm = expr->get_llvm_init(block);
    llvm += expr->get_llvm(block);
    return llvm;
}

std::string InvocationStatement::get_ssa(Bblock &block) {
    spdlog::debug("inside InvocationStatement::{}\n",__func__);
    auto expr = this->getExpression();
    std::string ssa = expr->get_ssa_init(block);
    ssa += expr->get_ssa(block);
    return ssa;
}

void InvocationStatement::resolve_def_uses(Bblock &block) {
    spdlog::debug("inside InvocationStatement::{}\n",__func__);
    this->expression->resolve_uses(block);
}

} // namespace ast

