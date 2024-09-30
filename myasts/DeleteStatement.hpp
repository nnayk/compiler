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

    // Getter for the expression
    std::shared_ptr<Expression> getExpression() const;

private:
    std::shared_ptr<Expression> expression_;
};

} // namespace ast

#endif // DELETE_STATEMENT_HPP

