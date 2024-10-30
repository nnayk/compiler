#ifndef CONDITIONALSTATEMENT_HPP
#define CONDITIONALSTATEMENT_HPP

#include "AbstractStatement.hpp"
#include "Expression.hpp"
#include "Statement.hpp"
#include <memory>

namespace ast {

class ConditionalStatement : public AbstractStatement { 
public:
    std::shared_ptr<Expression> guard;
    std::shared_ptr<Statement> thenBlock;
    std::shared_ptr<Statement> elseBlock;
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
	virtual std::vector<std::shared_ptr<Bblock>> get_cfg() override;
	virtual std::string get_llvm() override;
};

} // namespace ast

#endif // CONDITIONALSTATEMENT_HPP

