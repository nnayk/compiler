#ifndef RETURN_EMPTY_STATEMENT_HPP
#define RETURN_EMPTY_STATEMENT_HPP

#include "AbstractStatement.hpp"

namespace ast {

class ReturnEmptyStatement : public AbstractStatement {
public:
    // Constructor
    ReturnEmptyStatement(int lineNum);
    virtual std::string display() const override {
        return fmt::format("ReturnEmptyStatement(lineNum={})",lineNum);
    }
     void typecheck(Env &env,Function &f) override;
};


} // namespace ast

#endif // RETURN_EMPTY_STATEMENT_HPP

