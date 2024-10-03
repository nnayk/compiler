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
} // namespace ast

