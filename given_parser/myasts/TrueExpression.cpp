#include "TrueExpression.hpp"

namespace ast {

TrueExpression::TrueExpression(int lineNum)
    : AbstractExpression(lineNum) {
}

std::shared_ptr<Type> TrueExpression::resolveType(Env &env)  { return std::make_shared<BoolType>(); }

std::string TrueExpression::get_llvm() {
    return "1";
}

} // namespace ast

