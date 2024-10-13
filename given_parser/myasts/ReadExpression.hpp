#ifndef READ_EXPRESSION_HPP
#define READ_EXPRESSION_HPP

#include "AbstractExpression.hpp"

namespace ast {

// placeholder expr to read an int from stdin
class ReadExpression : public AbstractExpression {
public:
    // Constructor
    ReadExpression(int lineNum);
	std::shared_ptr<Type> resolveType(Env &env) override;
};

} // namespace ast

#endif // READ_EXPRESSION_HPP

