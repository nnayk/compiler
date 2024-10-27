#include "InvocationExpression.hpp"

extern std::string TAB;

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
    /*
    if(!func) {
   		throw TypeException(fmt::format("Attempt to invoke nonexistent function {}\n",name)); 
    }
    */
	this->type = func->retType;
    int actualArgs = args.size();
    int expectedArgs = func->params.size();
	if(args.size() != func->params.size()) {
        throw TypeException(fmt::format("Expected {} args, got {}",expectedArgs,actualArgs));
    }
	for(int index = 0; index < actualArgs; index++) {
        auto arg = args[index];
		auto actual_type = arg->resolveType(env);
        auto expected_type = func->params[index].getType();
        if(typeid(actual_type) != typeid(expected_type)) {
            throw TypeException(fmt::format("Expected type {} for arg {}, got type {}\n",*expected_type,index+1,*actual_type));
        } else {
            spdlog::debug(fmt::format("Arg is correct type: expected type {} for arg {}, got type {}\n",*expected_type,index+1,*actual_type));
        }
	} 
    return nullptr;
}

std::string InvocationExpression::get_llvm_init() {
    spdlog::debug("inside InvocationExpression::{}\n",__func__);
	std::string llvm = ""; 
	// load each arg
	for(auto arg : this->arguments) {
		llvm += arg->get_llvm_init();
	}
    return llvm;
}
 
std::string InvocationExpression::get_llvm() { 
    spdlog::debug("inside InvocationExpression::{}\n",__func__);
    std::string llvm = TAB+fmt::format("call {} @{}(",this->type->get_llvm(),this->name);
    int index = 0;
    int args_size = this->arguments.size();
	for(auto arg : this->arguments) {
		spdlog::debug("arg={}\n",*arg);
		llvm += fmt::format("{} noundef {}",arg->type->get_llvm(),arg->get_llvm());
        if(index<args_size-1) {
            llvm += ", ";
        } else {
            llvm += ")";
        }
		index++;
	}
	// call the function
	return llvm;
}

} // namespace ast

