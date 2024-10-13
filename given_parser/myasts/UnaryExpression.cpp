#include "UnaryExpression.hpp"

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
    if(typeid(operandType) == typeid(ast::IntType) || typeid(operandType) == typeid(ast::BoolType)) {
        return operandType;
    } else {
        throw TypeException(fmt::format("Invalid unary operand of type {}",*operandType));
    }
}

} // namespace ast

