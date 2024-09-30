#include "Function.hpp"

namespace ast {

// Constructor
Function::Function(int lineNum, const std::string& name,
                   const std::list<std::shared_ptr<Declaration>>& params,
                   std::shared_ptr<Type> retType,
                   const std::list<std::shared_ptr<Declaration>>& locals,
                   std::shared_ptr<Statement> body)
    : lineNum(lineNum), name(name), params(params),
      retType(retType), locals(locals), body(body) {}

// Getters
int Function::getLineNum() const {
    return lineNum;
}

const std::string& Function::getName() const {
    return name;
}

const std::list<std::shared_ptr<Declaration>>& Function::getParams() const {
    return params;
}

std::shared_ptr<Type> Function::getRetType() const {
    return retType;
}

const std::list<std::shared_ptr<Declaration>>& Function::getLocals() const {
    return locals;
}

std::shared_ptr<Statement> Function::getBody() const {
    return body;
}

} // namespace ast

