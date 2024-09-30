#include "Program.hpp"

namespace ast {

// Constructor initializes the types, decls, and funcs vectors
Program::Program(std::vector<TypeDeclaration*> types, std::vector<Declaration*> decls,
                 std::vector<Function*> funcs)
    : types(types), decls(decls), funcs(funcs) {}

} // namespace ast

