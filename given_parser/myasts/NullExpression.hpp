#ifndef NULL_EXPRESSION_HPP
#define NULL_EXPRESSION_HPP

#include "AbstractExpression.hpp"

namespace ast {

class NullExpression : public AbstractExpression {
public:
    // Constructor
    NullExpression(int lineNum) : AbstractExpression(lineNum) {}
    std::shared_ptr<Type> resolveType() override { return std::make_shared<NullType>(); }
};

} // namespace ast

#endif // NULL_EXPRESSION_HPP

