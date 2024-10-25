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
std::string AbstractExpression::get_llvm_init() {
    return "";
}

std::string AbstractExpression::get_llvm() {
    return "";
}

}  // namespace ast
