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
    std::string get_llvm() override; 
};

} // namespace ast

#endif // TRUEEXPRESSION_HPP

