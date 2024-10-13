#ifndef TRUEEXPRESSION_HPP
#define TRUEEXPRESSION_HPP

#include "AbstractExpression.hpp"

namespace ast {

class TrueExpression : public AbstractExpression {
public:
    std::shared_ptr<Type> resolveType(Env &env) override;
    TrueExpression(int lineNum);
};

} // namespace ast

#endif // TRUEEXPRESSION_HPP

