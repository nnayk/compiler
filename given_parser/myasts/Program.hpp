#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <vector>
#include "TypeDeclaration.hpp"
#include "Declaration.hpp"
#include "Function.hpp"

namespace ast {

class Program {
public:
    std::vector<std::shared_ptr<TypeDeclaration>> typeDecls; // Pointer to TypeDeclaration objects (global struct definitions)
    std::vector<std::shared_ptr<Declaration>> decls;     // Pointer to Declaration objects (pointer to global var declarations)
    std::vector<std::shared_ptr<Function>> funcs;        // Pointer to Function objects
    // Constructor
    Program();
};

} // namespace ast

#endif // PROGRAM_HPP

