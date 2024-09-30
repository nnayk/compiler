#ifndef FALSE_EXPRESSION_HPP
#define FALSE_EXPRESSION_HPP

#include "AbstractExpression.hpp"

namespace ast {

class FalseExpression : public AbstractExpression {
public:
    // Constructor
    FalseExpression(int lineNum);
};

} // namespace ast

#endif // FALSE_EXPRESSION_HPP

