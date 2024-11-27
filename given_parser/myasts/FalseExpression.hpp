#ifndef FALSE_EXPRESSION_HPP
#define FALSE_EXPRESSION_HPP

#include "AbstractExpression.hpp"

namespace ast {

class FalseExpression : public AbstractExpression, 
    public std::enable_shared_from_this<FalseExpression> {
public:
    // Constructor
    FalseExpression(int lineNum);
    std::shared_ptr<Type> resolveType(Env &env) override;
    std::string display() const override {
        return fmt::format("FalseExpression(lineNum={})\n",lineNum);
    }
    std::string get_llvm(Bblock &block) override;
	virtual std::string get_ssa(Bblock &block) override;
	virtual std::string get_arm(Bblock &block) override;
    void resolve_uses(Bblock &block) override;
};

} // namespace ast

#endif // FALSE_EXPRESSION_HPP

