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
	virtual std::string get_llvm_init() override;
	virtual std::string get_llvm() override;
    virtual std::shared_ptr<Register> getDerefResult() const override;
    virtual std::shared_ptr<Register> getResult() const override;

    // Virtual destructor to allow proper cleanup of derived objects
    virtual ~AbstractExpression() {}
    // Getter for lineNum
    int getLineNum() const;
};

}  // namespace ast

#endif  // ABSTRACT_EXPRESSION_HPP
