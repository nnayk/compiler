#ifndef ABSTRACT_STATEMENT_HPP
#define ABSTRACT_STATEMENT_HPP

#include "Statement.hpp"
#include "Env.hpp"

namespace ast {

class AbstractStatement : public Statement, public std::enable_shared_from_this<AbstractStatement> {
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
    virtual std::vector<std::shared_ptr<Bblock>> get_cfg() override;
};

}  // namespace ast

#endif  // ABSTRACT_STATEMENT_HPP
