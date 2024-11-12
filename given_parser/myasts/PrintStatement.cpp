#include "PrintStatement.hpp"
#include "Register.hpp"
#include "IntegerExpression.hpp"

extern std::string TAB;

namespace ast {

// Constructor initializes the base class and sets the expression
PrintStatement::PrintStatement(int lineNum, std::shared_ptr<Expression> expression, bool newLine)
    : AbstractStatement(lineNum), expression(expression), newLine(newLine) {}

void PrintStatement::typecheck(Env &env, Function &f) {
    spdlog::debug("inside PrintStatement::{}\n",__func__);
    auto arg_type = this->expression->resolveType(env);
    assert(dynamic_pointer_cast<IntType>(arg_type));
}

std::string PrintStatement::get_llvm(Bblock &block) {
    spdlog::debug("inside PrintStatement::{}\n",__func__);
    // Seems like function calls require a label/register? Noticed that if I don't store the return value of the function call llvm itself creates the assignment (try this by generating the llvm visual cfg). Additionally was getting a "label unexpected number" error when I did not allocate a "egiter" (technically a label) for the print call
    std::string formatter = "@.print";
    if(this->getNewLine()) formatter += "ln";
    std::string llvm  = this->expression->get_llvm_init(block); 
    Register::create();
    llvm +=  TAB+fmt::format("call i32 (ptr, ...) @printf(ptr noundef {}, i64 noundef {})\n",formatter,this->expression->get_llvm(block)); 
    return llvm;
}

void PrintStatement::resolve_def_uses(Bblock &block) {
    spdlog::debug("inside PrintStatement::{}\n",__func__);
    this->expression->resolve_uses();    
}

} // namespace ast

