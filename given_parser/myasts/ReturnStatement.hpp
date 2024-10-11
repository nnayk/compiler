#ifndef RETURN_STATEMENT_HPP
#define RETURN_STATEMENT_HPP

#include "AbstractStatement.hpp"
#include "Expression.hpp"
#include <memory>

namespace ast {

class ReturnStatement : public AbstractStatement {
private:
    std::shared_ptr<Expression> expression; // Pointer to the expression

public:
    // Constructor
    ReturnStatement(int lineNum, std::shared_ptr<Expression> expression);
	// Virtual function for display
    std::string display() const override {
        return fmt::format("ReturnStatement(lineNum={})", lineNum);
    }
     void typecheck(Env &env) override;
};

} // namespace ast

#endif // RETURN_STATEMENT_HPP

