#ifndef UNARYEXPRESSION_HPP
#define UNARYEXPRESSION_HPP

#include <string>
#include <memory>
#include "AbstractExpression.hpp"

namespace ast {

class UnaryExpression : public AbstractExpression {
public:
    enum class Operator {
        NOT,
        MINUS
    };
    static std::shared_ptr<UnaryExpression> create(int lineNum, const std::string& opStr, std::shared_ptr<Expression> operand);
    UnaryExpression(int lineNum, Operator operatorType, std::shared_ptr<Expression> operand);
private:
    Operator operatorType;
    std::shared_ptr<Expression> operand;

};

}
#endif
