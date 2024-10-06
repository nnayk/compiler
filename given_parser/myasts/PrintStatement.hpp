#ifndef PRINT_STATEMENT_HPP
#define PRINT_STATEMENT_HPP

#include "AbstractStatement.hpp"
#include "Expression.hpp"

namespace ast {

class PrintStatement : public AbstractStatement {
private:
    Expression* expression; // Pointer to the expression to print

public:
    // Constructor
    PrintStatement(int lineNum, Expression* expression);
    
    // Destructor
    virtual ~PrintStatement() = default; // Default destructor
};

} // namespace ast

#endif // PRINT_STATEMENT_HPP

