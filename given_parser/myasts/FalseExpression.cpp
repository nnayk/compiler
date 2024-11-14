#include "FalseExpression.hpp"

namespace ast {

// Constructor
FalseExpression::FalseExpression(int lineNum)
    : AbstractExpression(lineNum) {}

std::shared_ptr<Type> FalseExpression::resolveType(Env &env)  { 
    this->type = std::make_shared<BoolType>(); 
    return this->type;
}

std::string FalseExpression::get_llvm(Bblock &block) {
    return "0";
}

void FalseExpression::resolve_uses(Bblock &block) {
    spdlog::debug("inside FalseExpression::{}\n",__func__);
    auto id = this->get_llvm(block);
    // I don't think it matters if is_global is set to true or false here...
    // We're dealing with an immediate, not a variable so it doesn't matter
    this->result = Register::create(id,false,true);
}

} // namespace ast

