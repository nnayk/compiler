#ifndef INVOCATION_EXPRESSION_HPP
#define INVOCATION_EXPRESSION_HPP

#include "AbstractExpression.hpp"
#include <string>
#include <vector>
#include <memory>
#include "Program.hpp"

extern ast::Program p;

namespace ast {

class InvocationExpression : public AbstractExpression {
public:
    std::string name; // The name of the invoked function
    std::vector<std::shared_ptr<Expression>> arguments; // List of arguments
    // Constructor
    InvocationExpression(int lineNum, const std::string& name,
                        const std::vector<std::shared_ptr<Expression>>& arguments);
	std::shared_ptr<Type> resolveType(Env &env) override;
    // Getter for the name
    std::string getName() const;

    // Getter for the arguments
    std::vector<std::shared_ptr<Expression>> getArguments() const;
};

} // namespace ast

#endif // INVOCATION_EXPRESSION_HPP

