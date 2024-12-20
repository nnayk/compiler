#ifndef CONDITIONALSTATEMENT_HPP
#define CONDITIONALSTATEMENT_HPP

#include "AbstractStatement.hpp"
#include "Expression.hpp"
#include "Statement.hpp"
#include "Label.hpp"
#include <memory>

namespace ast {

class ConditionalStatement : public AbstractStatement { 
public:
    std::shared_ptr<Expression> guard;
    std::shared_ptr<Statement> thenBlock;
    std::shared_ptr<Statement> elseBlock;
    //std::shared_ptr<Label> thenLabel = nullptr;
    //std::shared_ptr<Label> elseLabel = nullptr;
    //std::shared_ptr<Label> afterLabel = nullptr;
    // Constructor
    ConditionalStatement(int lineNum, 
                         std::shared_ptr<Expression> guard, 
                         std::shared_ptr<Statement> thenBlock, 
                         std::shared_ptr<Statement> elseBlock);

    // Destructor
    virtual ~ConditionalStatement() = default;
    virtual void typecheck(Env &env, Function &f) override;
    virtual std::string get_arm(Bblock &block) override;
    std::string display() const override {
        return fmt::format("ConditionalStatement(lineNum={})",lineNum);
    }
	virtual std::vector<std::shared_ptr<Bblock>> get_cfg() override;
	virtual std::string get_llvm(Bblock &block) override;
    virtual std::string get_ssa(Bblock &block) override;
    virtual void resolve_def_uses(Bblock &block) override;
    virtual bool guarantees_return(std::shared_ptr<Type> type) override; 
};

} // namespace ast

#endif // CONDITIONALSTATEMENT_HPP

