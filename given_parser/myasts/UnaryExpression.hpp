#ifndef UNARYEXPRESSION_HPP
#define UNARYEXPRESSION_HPP

#include <string>
#include <memory>
#include "AbstractExpression.hpp"
#include "TrueExpression.hpp"
#include "FalseExpression.hpp"

namespace ast {

class UnaryExpression : public AbstractExpression {
public:
    enum class Operator {
        NOT,
        MINUS
    };
    static std::shared_ptr<UnaryExpression> create(int lineNum, const std::string& opStr, std::shared_ptr<Expression> operand);
    UnaryExpression(int lineNum, Operator operatorType, std::shared_ptr<Expression> operand);
    Operator getOperatorType() const { return operatorType; }
    std::shared_ptr<Expression> getOperand() const { return operand; } 
    std::string display() const override {
        auto output = fmt::format("UnaryExpression(lineNum={},operator={},operand={})\n",
                                   lineNum,static_cast<int>(this->getOperatorType()),*this->getOperand());
        output+="\n";
        return output;
    }
    std::string get_llvm(Bblock &block) override; 
private:
    Operator operatorType;
    std::shared_ptr<Expression> operand;
    std::shared_ptr<Type> resolveType(Env &env) override;

};

}
#endif
