#include "BinaryExpression.hpp"

namespace ast {

// Private constructor definition
BinaryExpression::BinaryExpression(int lineNum, Operator operatorType,
                                   std::shared_ptr<Expression> left,
                                   std::shared_ptr<Expression> right)
    : AbstractExpression(lineNum), operatorType(operatorType), left(left), right(right) {}

// Static factory method definition
std::shared_ptr<BinaryExpression> BinaryExpression::create(int lineNum, const std::string& opStr,
                                                          std::shared_ptr<Expression> left,
                                                          std::shared_ptr<Expression> right) {
    if (opStr == "*") {
        return std::shared_ptr<BinaryExpression>(new BinaryExpression(lineNum, Operator::TIMES, left, right));
    } else if (opStr == "/") {
        return std::shared_ptr<BinaryExpression>(new BinaryExpression(lineNum, Operator::DIVIDE, left, right));
    } else if (opStr == "+") {
        return std::shared_ptr<BinaryExpression>(new BinaryExpression(lineNum, Operator::PLUS, left, right));
    } else if (opStr == "-") {
        return std::shared_ptr<BinaryExpression>(new BinaryExpression(lineNum, Operator::MINUS, left, right));
    } else if (opStr == "<") {
        return std::shared_ptr<BinaryExpression>(new BinaryExpression(lineNum, Operator::LT, left, right));
    } else if (opStr == "<=") {
        return std::shared_ptr<BinaryExpression>(new BinaryExpression(lineNum, Operator::LE, left, right));
    } else if (opStr == ">") {
        return std::shared_ptr<BinaryExpression>(new BinaryExpression(lineNum, Operator::GT, left, right));
    } else if (opStr == ">=") {
        return std::shared_ptr<BinaryExpression>(new BinaryExpression(lineNum, Operator::GE, left, right));
    } else if (opStr == "==") {
        return std::shared_ptr<BinaryExpression>(new BinaryExpression(lineNum, Operator::EQ, left, right));
    } else if (opStr == "!=") {
        return std::shared_ptr<BinaryExpression>(new BinaryExpression(lineNum, Operator::NE, left, right));
    } else if (opStr == "&&") {
        return std::shared_ptr<BinaryExpression>(new BinaryExpression(lineNum, Operator::AND, left, right));
    } else if (opStr == "||") {
        return std::shared_ptr<BinaryExpression>(new BinaryExpression(lineNum, Operator::OR, left, right));
    } else {
        throw std::invalid_argument("Invalid operator string: " + opStr);
    }
}

}  // namespace ast
