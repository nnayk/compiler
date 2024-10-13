#include "ReadExpression.hpp"

namespace ast {

// Constructor that calls the base class constructor
ReadExpression::ReadExpression(int lineNum)
    : AbstractExpression(lineNum) {}

std::shared_ptr<Type> ReadExpression::resolveType(Env &env) {
	return std::make_shared<ast::IntType>();
}

} // namespace ast

