#include "UnaryExpression.hpp"
#include <typeinfo>

namespace ast {

UnaryExpression::UnaryExpression(int lineNum, Operator operatorType, std::shared_ptr<Expression> operand)
    : AbstractExpression(lineNum), operatorType(operatorType), operand(operand) {
}

std::shared_ptr<UnaryExpression> UnaryExpression::create(int lineNum, const std::string& opStr, std::shared_ptr<Expression> operand) {
    if (opStr == "!") {
        return std::make_shared<UnaryExpression>(lineNum, Operator::NOT, operand);
    } else if (opStr == "-") {
        return std::make_shared<UnaryExpression>(lineNum, Operator::MINUS, operand);
    } else {
        throw std::invalid_argument("Invalid operator");
    }
}

std::shared_ptr<Type> UnaryExpression::resolveType(Env &env) {
    auto operandType = this->getOperand()->resolveType(env);
    // only valid operand types are ints or bools
    if(dynamic_pointer_cast<ast::IntType>(operandType) || dynamic_pointer_cast<ast::BoolType>(operandType)) {
        this->type = operandType;
        return this->type;
    } else {
        throw TypeException(fmt::format("Invalid unary operand of type {}",*operandType));
    }
}

std::string UnaryExpression::get_llvm(Bblock &block) {
    auto operand_llvm = this->getOperand()->get_llvm(block);
    if(dynamic_pointer_cast<ast::IntType>(this->type)) {
        return fmt::format("-{}",operand_llvm);
    } else {
        // hardcoding get_llvm for True/False Expr for now
        if(dynamic_pointer_cast<TrueExpression>(this->getOperand())) {
            return "0";
        } else {
            return "1";
        }
    }
}

void UnaryExpression::resolve_uses(Bblock &block) {
    spdlog::debug("inside UnaryExpression::{}\n",__func__);
    this->result = Register::create();
    spdlog::debug("chose register {} for UnaryExpression on line {}\n",*this->result,this->getLineNum());
}

} // namespace ast

