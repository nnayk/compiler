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

} // namespace ast

