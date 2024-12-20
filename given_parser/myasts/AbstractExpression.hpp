#ifndef ABSTRACT_EXPRESSION_HPP
#define ABSTRACT_EXPRESSION_HPP

#include "Expression.hpp"

namespace ast {

class AbstractExpression : public Expression {
protected:
    const int lineNum;  // Equivalent to 'private final int' in Java

public:
    // Constructor
    AbstractExpression(int lineNum);
	virtual std::string get_llvm_init(Bblock &block) override;
	virtual std::string get_llvm(Bblock &block) override;
	virtual std::string get_ssa_init(Bblock &block) override;
	virtual std::string get_ssa(Bblock &block) override;
    virtual std::string get_arm_init(Bblock &block) override; 
    virtual std::shared_ptr<Register> getDerefResult() const override;
    virtual std::shared_ptr<Register> getResult() const override;
    virtual void replace_reg(std::shared_ptr<Register> target,std::shared_ptr<Register> sub) override;

    // Virtual destructor to allow proper cleanup of derived objects
    virtual ~AbstractExpression() {}
    // Getter for lineNum
    int getLineNum() const;
    virtual void resolve_uses(Bblock &block) override;
    virtual std::string get_arm(Bblock &block) override;
};
}  // namespace ast

#endif  // ABSTRACT_EXPRESSION_HPP
