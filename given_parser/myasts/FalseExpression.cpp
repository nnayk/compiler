#include "FalseExpression.hpp"

namespace ast {

// Constructor
FalseExpression::FalseExpression(int lineNum)
    : AbstractExpression(lineNum) {}

std::shared_ptr<Type> FalseExpression::resolveType(Env &env)  { return std::make_shared<BoolType>(); }

std::string FalseExpression::get_llvm() {
    return "0";
}
} // namespace ast

