#ifndef READ_EXPRESSION_HPP
#define READ_EXPRESSION_HPP

#include "AbstractExpression.hpp"

namespace ast {

class ReadExpression : public AbstractExpression {
public:
    // Constructor
    ReadExpression(int lineNum);
};

} // namespace ast

#endif // READ_EXPRESSION_HPP

