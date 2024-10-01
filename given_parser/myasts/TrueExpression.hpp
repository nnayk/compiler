#ifndef TRUEEXPRESSION_HPP
#define TRUEEXPRESSION_HPP

#include "AbstractExpression.hpp"

namespace ast {

class TrueExpression : public AbstractExpression {
public:
    TrueExpression(int lineNum);
};

} // namespace ast

#endif // TRUEEXPRESSION_HPP

