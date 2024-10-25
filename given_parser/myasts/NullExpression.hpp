#ifndef NULL_EXPRESSION_HPP
#define NULL_EXPRESSION_HPP

#include "AbstractExpression.hpp"

namespace ast {

class NullExpression : public AbstractExpression {
public:
    // Constructor
    NullExpression(int lineNum) : AbstractExpression(lineNum) {}
    std::shared_ptr<Type> resolveType(Env &env) override { return std::make_shared<NullType>(); }
    std::string display() const override {
        auto output = fmt::format("NullExpression(lineNum={})",lineNum);
        output+="\n";
        return output;
    }
};

} // namespace ast

#endif // NULL_EXPRESSION_HPP

