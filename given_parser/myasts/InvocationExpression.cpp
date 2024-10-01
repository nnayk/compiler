#include "InvocationExpression.hpp"

namespace ast {

// Constructor
InvocationExpression::InvocationExpression(int lineNum, const std::string& name,
                                           const std::vector<std::shared_ptr<Expression>>& arguments)
    : AbstractExpression(lineNum), name(name), arguments(arguments) {}

// Getter for the name
std::string InvocationExpression::getName() const {
    return name;
}

// Getter for the arguments
std::vector<std::shared_ptr<Expression>> InvocationExpression::getArguments() const {
    return arguments;
}

} // namespace ast

