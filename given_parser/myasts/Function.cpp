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
    spdlog::info("inside Function::{}\n",__func__);
    spdlog::debug("adding binding from _ret to {}\n",*this->retType);
    auto ret_entry = std::make_shared<Entry>(this->retType);
    ret_entry->scope = 0;
    env.addBinding("_ret",ret_entry);
    body->typecheck(env,*this);        
    // TODO:#2+#3 from description
    return;
}

const std::string& Function::getName() const {
    return this->name;
}

} // namespace ast

