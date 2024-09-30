#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <vector>
#include "TypeDeclaration.hpp"
#include "Declaration.hpp"
#include "Function.hpp"

namespace ast {

class Program {
private:
    std::vector<TypeDeclaration*> types; // Pointer to TypeDeclaration objects
    std::vector<Declaration*> decls;     // Pointer to Declaration objects
    std::vector<Function*> funcs;        // Pointer to Function objects

public:
    // Constructor
    Program(std::vector<TypeDeclaration*> types, std::vector<Declaration*> decls,
            std::vector<Function*> funcs);
};

} // namespace ast

#endif // PROGRAM_HPP

