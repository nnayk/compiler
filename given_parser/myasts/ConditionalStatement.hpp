#ifndef CONDITIONALSTATEMENT_HPP
#define CONDITIONALSTATEMENT_HPP

#include "AbstractStatement.hpp"
#include "Expression.hpp"
#include "Statement.hpp"
#include <memory>

namespace ast {

class ConditionalStatement : public AbstractStatement {
private:
    std::shared_ptr<Expression> guard;
    std::shared_ptr<Statement> thenBlock;
    std::shared_ptr<Statement> elseBlock;

public:
    // Constructor
    ConditionalStatement(int lineNum, 
                         std::shared_ptr<Expression> guard, 
                         std::shared_ptr<Statement> thenBlock, 
                         std::shared_ptr<Statement> elseBlock);

    // Destructor
    virtual ~ConditionalStatement() = default;
    virtual void typecheck(Env &env) override;
    std::string display() const override {
        return fmt::format("ConditionalStatement(lineNum={})",lineNum);
    }
};

} // namespace ast

#endif // CONDITIONALSTATEMENT_HPP

