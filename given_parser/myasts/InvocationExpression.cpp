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

/*
Typechecks the function params and returns the return type of the function
being called
*/
std::shared_ptr<Type> InvocationExpression::resolveType(Env &env) {
	// Check that the types of the params match the expected types of the 
	// function params (also check that the function exists in the 1st place)
	auto args = this->getArguments();
    auto func = p.getFunction(name);
    if(!func) {
    
    }
    int actualArgs = args.size();
    int expectedArgs = func->params.size();
	if(args.size() != func->params.size()) {
        throw TypeException(fmt::format("Expected {} args, got {}",expectedArgs,actualArgs));
    }
	for(auto arg : args) {
		arg->resolveType(env);
	} 
    return nullptr;
} 

} // namespace ast

