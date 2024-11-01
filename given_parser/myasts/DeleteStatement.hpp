#ifndef DELETE_STATEMENT_HPP
#define DELETE_STATEMENT_HPP

#include "AbstractStatement.hpp"
#include "Expression.hpp"
#include <memory>

namespace ast {

class DeleteStatement : public AbstractStatement {
public:
    // Constructor
    DeleteStatement(int lineNum, std::shared_ptr<Expression> expression);
	void typecheck(Env &env, Function &f) override;
    // Getter for the expression
    std::shared_ptr<Expression> getExpression() const;
    std::string display() const override {
        return fmt::format("DeleteStatement(lineNum={})",lineNum);
    }

private:
    std::shared_ptr<Expression> expression_;
};

} // namespace ast

#endif // DELETE_STATEMENT_HPP

