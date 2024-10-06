#ifndef INVOCATION_EXPRESSION_HPP
#define INVOCATION_EXPRESSION_HPP

#include "AbstractExpression.hpp"
#include <string>
#include <vector>
#include <memory>

namespace ast {

class InvocationExpression : public AbstractExpression {
public:
    std::string name; // The name of the invoked function
    std::vector<std::shared_ptr<Expression>> arguments; // List of arguments
    // Constructor
    InvocationExpression(int lineNum, const std::string& name,
                        const std::vector<std::shared_ptr<Expression>>& arguments);

    // Getter for the name
    std::string getName() const;

    // Getter for the arguments
    std::vector<std::shared_ptr<Expression>> getArguments() const;
};

} // namespace ast

#endif // INVOCATION_EXPRESSION_HPP

