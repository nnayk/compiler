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
	virtual std::string get_llvm() override;

    // Virtual destructor to allow proper cleanup of derived objects
    virtual ~AbstractExpression() {}
    // Getter for lineNum
    int getLineNum() const;
    //std::string get_llvm();
};

}  // namespace ast

#endif  // ABSTRACT_EXPRESSION_HPP
