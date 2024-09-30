#ifndef UNARYEXPRESSION_HPP
#define UNARYEXPRESSION_HPP

#include <string>
#include <memory>
#include "AbstractExpression.hpp"

namespace ast {

class UnaryExpression : public AbstractExpression {
private:
    Operator operatorType;
    std::shared_ptr<Expression> operand;

    UnaryExpression(int lineNum, Operator operatorType, std::shared_ptr<Expression> operand);

public:
    static UnaryExpression create(int lineNum, const std::string& opStr, std::shared_ptr<Expression> operand);

    enum class Operator {
        NOT,
        MINUS
    };

    int getLineNum() const {
        return lineNum; // Assuming you have a way

