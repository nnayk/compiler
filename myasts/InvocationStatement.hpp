#ifndef INVOCATION_STATEMENT_HPP
#define INVOCATION_STATEMENT_HPP

#include "AbstractStatement.hpp"
#include <memory>

namespace ast {

class InvocationStatement : public AbstractStatement {
public:
    // Constructor
    InvocationStatement(int lineNum, std::shared_ptr<Expression> expression);

    // Getter for the expression
    std::shared_ptr<Expression> getExpression() const;

private:
    std::shared_ptr<Expression> expression; // The expression to be invoked
};

} // namespace ast

#endif // INVOCATION_STATEMENT_HPP

