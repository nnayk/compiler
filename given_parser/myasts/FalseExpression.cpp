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
} // namespace ast

