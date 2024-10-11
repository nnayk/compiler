#ifndef INVOCATION_STATEMENT_HPP
#define INVOCATION_STATEMENT_HPP

#include "AbstractStatement.hpp"
#include <memory>
#include "Expression.hpp"

namespace ast {

class InvocationStatement : public AbstractStatement {
public:
    // Constructor
    InvocationStatement(int lineNum, std::shared_ptr<Expression> expression);

    // Getter for the expression
    std::shared_ptr<Expression> getExpression() const;
 	
	std::string display() const override {
     	return fmt::format("InovcationStatement(lineNum={})",lineNum);
 	}
	
	void typecheck(Env &env) override;

private:
    std::shared_ptr<Expression> expression; // The expression to be invoked
};

} // namespace ast

#endif // INVOCATION_STATEMENT_HPP

