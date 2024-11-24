#ifndef RETURN_STATEMENT_HPP
#define RETURN_STATEMENT_HPP

#include "AbstractStatement.hpp"
#include "Expression.hpp"
#include <memory>

namespace ast {

class ReturnStatement : public AbstractStatement {
private:
    std::shared_ptr<Expression> expression; // Pointer to the expression
public:
    std::shared_ptr<Type> retType = nullptr;
    bool final_return = false;
    // Constructor
    ReturnStatement(int lineNum, std::shared_ptr<Expression> expression);
	// Virtual function for display
    std::string display() const override {
        return fmt::format("ReturnStatement(lineNum={})", this->getLineNum());
    }
     void typecheck(Env &env, Function &f) override;
     std::string get_llvm(Bblock &block) override;
     virtual std::string get_ssa(Bblock &block) override;
     virtual std::string get_arm(Bblock &block) override;
     virtual std::vector<std::shared_ptr<Bblock>> get_cfg() override;
     virtual void resolve_def_uses(Bblock &block) override;
};

} // namespace ast

#endif // RETURN_STATEMENT_HPP

