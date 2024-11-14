#include "AbstractExpression.hpp"

namespace ast {

// Constructor definition
AbstractExpression::AbstractExpression(int lineNum) : lineNum(lineNum) {}

// Getter for lineNum
int AbstractExpression::getLineNum() const {
    return lineNum;
}

/* Generates LLVM IR for the expression and returns the temporary register
where the result is stored. (If it's an assignment operator then returns
the target "register").
*/
std::string AbstractExpression::get_llvm_init(Bblock &block) {
    return "";
}

std::string AbstractExpression::get_llvm(Bblock &block) {
    return "";
}

std::shared_ptr<Register> AbstractExpression::getResult() const {
    return this->result;
}

std::shared_ptr<Register> AbstractExpression::getDerefResult() const {
    return this->deref_result;
}

void AbstractExpression::resolve_uses(Bblock &block) {
    spdlog::debug("AbstractExpression::{}\n",__func__);
}

std::string AbstractExpression::get_ssa_init(Bblock &block) {
    spdlog::debug("inside AbstractExpression::{}\n",__func__);
    return "";
}

std::string AbstractExpression::get_ssa(Bblock &block) {
    spdlog::debug("inside AbstractExpression::{}\n",__func__);
    return "";
}

}  // namespace ast
