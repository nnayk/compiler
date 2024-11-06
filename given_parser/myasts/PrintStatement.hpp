#ifndef PRINT_STATEMENT_HPP
#define PRINT_STATEMENT_HPP

#include "AbstractStatement.hpp"
#include "Expression.hpp"
#include <memory>

namespace ast {

class PrintStatement : public AbstractStatement {
private:
    std::shared_ptr<Expression> expression; // Pointer to the expression to print
    bool newLine;
public:
    // Constructor
    PrintStatement(int lineNum, std::shared_ptr<Expression> expression, bool newLine);
    
    // Destructor
    virtual ~PrintStatement() = default; // Default destructor
    bool getNewLine() {return newLine;}
    std::shared_ptr<Expression> getExpression() {return expression;}
    std::string display() const override {
            return fmt::format("PrintStatement(lineNum={},newLine?={})",lineNum,newLine);
    }
    virtual void typecheck(Env &env, Function &f) override;
    std::string get_llvm(Bblock &block) override;
};

} // namespace ast

#endif // PRINT_STATEMENT_HPP

