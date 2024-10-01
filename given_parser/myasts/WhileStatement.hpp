#ifndef WHILESTATEMENT_HPP
#define WHILESTATEMENT_HPP

#include "AbstractStatement.hpp"
#include "Expression.hpp"
#include "Statement.hpp"

namespace ast {

class WhileStatement : public AbstractStatement {
private:
    Expression* guard;  // Pointer for polymorphic behavior
    Statement* body;    // Pointer for polymorphic behavior

public:
    WhileStatement(int lineNum, Expression* guard, Statement* body);
};

} // namespace ast

#endif // WHILESTATEMENT_HPP

