#ifndef ASSIGNMENT_STATEMENT_HPP
#define ASSIGNMENT_STATEMENT_HPP

#include "AbstractStatement.hpp"
#include "Lvalue.hpp"
#include "Expression.hpp"
#include <memory>

namespace ast {

class AssignmentStatement : public AbstractStatement {
private:
    std::shared_ptr<Lvalue> target;   // Pointer for target to manage memory
    std::shared_ptr<Expression> source; // Pointer for source to manage memory

public:
    // Constructor
    AssignmentStatement(int lineNum, std::shared_ptr<Lvalue> target, std::shared_ptr<Expression> source);

    // Getter for target
    std::shared_ptr<Lvalue> getTarget() const;

    // Getter for source
    std::shared_ptr<Expression> getSource() const;
};

}  // namespace ast

#endif  // ASSIGNMENT_STATEMENT_HPP