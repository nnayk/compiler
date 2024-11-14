#ifndef BINARY_EXPRESSION_HPP
#define BINARY_EXPRESSION_HPP

#include "AbstractExpression.hpp"
#include "Expression.hpp"
#include <memory>
#include <stdexcept>
#include <string>

namespace ast {

class BinaryExpression : public AbstractExpression {
public:
    enum class Operator {
        TIMES, DIVIDE, PLUS, MINUS, LT, GT, LE, GE, EQ, NE, AND, OR
    };

private:
    Operator operatorType;  // Use a type for the operator
    std::shared_ptr<Expression> left;   // Pointer to the left expression
    std::shared_ptr<Expression> right;  // Pointer to the right expression
    // Private constructor
    BinaryExpression(int lineNum, Operator operatorType,
                     std::shared_ptr<Expression> left, std::shared_ptr<Expression> right);

public:
    // Static factory method
    static std::shared_ptr<BinaryExpression> create(int lineNum, const std::string& opStr,
                                                    std::shared_ptr<Expression> left,
                                                    std::shared_ptr<Expression> right);

    // Operator getter (if needed)
    Operator getOperator() const { return operatorType; }
    std::shared_ptr<Expression> getLeft() const { return left; }
    std::shared_ptr<Expression> getRight() const { return right; }
    std::string display() const override {
        return fmt::format("BinaryExpression(lineNum={},left={},operator={},right={}\n)"
                            ,lineNum,*this->getLeft(),static_cast<int>(this->getOperator()),*this->getRight());
    }
    std::string get_llvm_init(Bblock &block) override;
    std::string get_llvm(Bblock &block) override;
	virtual std::string get_ssa_init(Bblock &block) override;
	virtual std::string get_ssa(Bblock &block) override;
    std::shared_ptr<Type> resolveType(Env &env) override;
    bool is_i1(); 
    std::string zext(); 
    void resolve_uses(Bblock &block) override;
};

}  // namespace ast

#endif  // BINARY_EXPRESSION_HPP
