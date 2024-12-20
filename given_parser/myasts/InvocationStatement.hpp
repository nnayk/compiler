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
	
	void typecheck(Env &env, Function &f) override;
    virtual std::string get_llvm(Bblock &block) override;
    virtual std::string get_ssa(Bblock &block) override;
    virtual void resolve_def_uses(Bblock &block) override;

private:
    std::shared_ptr<Expression> expression; // The expression to be invoked
};

} // namespace ast

#endif // INVOCATION_STATEMENT_HPP

