#ifndef PRINT_LN_STATEMENT_HPP
#define PRINT_LN_STATEMENT_HPP

#include "AbstractStatement.hpp"
#include "Expression.hpp"

namespace ast {

class PrintLnStatement : public AbstractStatement {
private:
    Expression* expression; // Pointer to the expression to print

public:
    // Constructor
    PrintLnStatement(int lineNum, Expression* expression);

    // Destructor
    virtual ~PrintLnStatement() = default; // Default destructor
};

} // namespace ast

#endif // PRINT_LN_STATEMENT_HPP

