#include "UnaryExpression.hpp"
#include "IdentifierExpression.hpp"
#include <typeinfo>
#include "utils.hpp"

extern std::string TAB;
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

std::string UnaryExpression::get_ssa_init(Bblock &block) {
    spdlog::debug("inside UnaryExpression::{}\n",__func__);
    auto operand = this->operand;
    assert(operand);
    // NOTE: since get_llvm+init only handle immediates rn, I'm rewriting the logic in get_ssa+init to handle immediates as well as variables
    if(is_immediate(operand)) {
        spdlog::debug("expresion is an immediate, no llvm init needed\n");
        return "";
    } else {
        // Not supporting negations of compound expressions (ex. -(4+5)) for
        // now. So the only other possibility is an IdExpr.
        assert(dynamic_pointer_cast<ast::IdentifierExpression>(operand));
        spdlog::debug("expresion is NOT an immediate, llvm init needed\n");
        if(dynamic_pointer_cast<ast::IntType>(this->type)) {
            spdlog::debug("{} is an int, gonna negate it!\n",*operand);
            return TAB+fmt::format("{} = sub i32 0, {}\n",this->result->get_llvm(),operand->get_llvm(block));
        } else {
            spdlog::debug("{} is a bool, gonna negate it!\n",*operand);
            return TAB+fmt::format("{} = xor i1 {}, 1\n",this->result->get_llvm(),operand->get_llvm(block));
        }
    }
}

std::string UnaryExpression::get_ssa(Bblock &block) {
    spdlog::debug("inside UnaryExpression::{}\n",__func__);
    return this->result->get_llvm();
}

void UnaryExpression::resolve_uses(Bblock &block) {
    spdlog::debug("inside UnaryExpression::{}\n",__func__);
    this->result = Register::create();
    spdlog::debug("chose register {} for UnaryExpression on line {}\n",*this->result,this->getLineNum());
}

} // namespace ast

