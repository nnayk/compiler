#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <vector>
#include "TypeDeclaration.hpp"
#include "Declaration.hpp"
#include "Function.hpp"

namespace ast {

class Program {
public:
    std::vector<TypeDeclaration*> typeDecls; // Pointer to TypeDeclaration objects
    std::vector<Declaration*> decls;     // Pointer to Declaration objects
    std::vector<Function*> funcs;        // Pointer to Function objects
    // Constructor
    Program();
    ~Program();
};

} // namespace ast

#endif // PROGRAM_HPP

