#ifndef ABSTRACT_STATEMENT_HPP
#define ABSTRACT_STATEMENT_HPP

#include "Statement.hpp"

namespace ast {

class AbstractStatement : public Statement {
protected:
    const int lineNum;  // Equivalent to 'private final int' in Java

public:
    // Constructor
    AbstractStatement(int lineNum);

    // Virtual destructor for proper cleanup of derived objects
    virtual ~AbstractStatement() {}

    // Getter for lineNum
    int getLineNum() const;
};

}  // namespace ast

#endif  // ABSTRACT_STATEMENT_HPP
