#ifndef TRUEEXPRESSION_HPP
#define TRUEEXPRESSION_HPP

#include "AbstractExpression.hpp"

namespace ast {

class TrueExpression : public AbstractExpression {
public:
    std::shared_ptr<Type> resolveType(Env &env) override;
    TrueExpression(int lineNum);
    std::string display() const override {
        return fmt::format("TrueExpression(lineNum={})\n",lineNum);
    }
    std::string get_llvm(Bblock &block) override;
    std::string get_ssa(Bblock &block) override;
	virtual std::string get_arm(Bblock &block) override;
    void resolve_uses(Bblock &block) override;
};

} // namespace ast

#endif // TRUEEXPRESSION_HPP

