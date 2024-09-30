#ifndef NULL_EXPRESSION_HPP
#define NULL_EXPRESSION_HPP

#include "AbstractExpression.hpp"

namespace ast {

class NullExpression : public AbstractExpression {
public:
    // Constructor
    NullExpression(int lineNum) : AbstractExpression(lineNum) {}
};

} // namespace ast

#endif // NULL_EXPRESSION_HPP

