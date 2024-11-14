#include "TrueExpression.hpp"

namespace ast {

TrueExpression::TrueExpression(int lineNum)
    : AbstractExpression(lineNum) {
}

std::shared_ptr<Type> TrueExpression::resolveType(Env &env)  { 
    this->type = std::make_shared<BoolType>(); 
    return this->type;
}

std::string TrueExpression::get_llvm(Bblock &block) {
    return "1";
}

void TrueExpression::resolve_uses(Bblock &block) {
    spdlog::debug("inside TrueExpression::{}\n",__func__);
    auto id = this->get_llvm(block);
    this->result = Register::create(id,false,true);
}

} // namespace ast

