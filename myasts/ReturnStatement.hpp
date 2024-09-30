#ifndef RETURN_STATEMENT_HPP
#define RETURN_STATEMENT_HPP

#include "AbstractStatement.hpp"
#include "Expression.hpp"

namespace ast {

class ReturnStatement : public AbstractStatement {
private:
    Expression* expression; // Pointer to the expression

public:
    // Constructor
    ReturnStatement(int lineNum, Expression* expression);
};

} // namespace ast

#endif // RETURN_STATEMENT_HPP

