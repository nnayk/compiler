#include "Function.hpp"
#include <spdlog/spdlog.h>

namespace ast {

// Constructor
Function::Function(int lineNum, const std::string& name,
                   const std::vector<Declaration>& params,
                   std::shared_ptr<Type> retType, const std::vector<Declaration>& locals,
                   std::shared_ptr<Statement> body) : lineNum(lineNum), name(name), params(params),
                   retType(retType), locals(locals), body(body) {}

/*
Typecheck the given function as follows:
1. Typecheck each statement
2. Validate all control flow paths return expected type
3. Check there's a main function that takes no params and returns an int
*/
void Function::typecheck(Env env) { //TODO: check that env is a copy of tle
    body->typecheck(env);        
    // TODO:#2 from description
    return;
}
} // namespace ast

