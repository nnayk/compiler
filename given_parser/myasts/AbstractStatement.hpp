#ifndef ABSTRACT_STATEMENT_HPP
#define ABSTRACT_STATEMENT_HPP

#include "Statement.hpp"

namespace ast {

class AbstractStatement : public Statement {
public:
    int lineNum;  // Equivalent to 'private final int' in Java
    // Constructor
    AbstractStatement(int lineNum);

    // Virtual destructor for proper cleanup of derived objects
    virtual ~AbstractStatement() {}
	
	int getLineNum() const override {
        return this->lineNum;
    }

    void setLineNum(int line) {
        this->lineNum = line;
    }
};

}  // namespace ast

#endif  // ABSTRACT_STATEMENT_HPP
