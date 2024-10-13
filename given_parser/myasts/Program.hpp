#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <vector>
#include "TypeDeclaration.hpp"
#include "Declaration.hpp"
#include "Function.hpp"

namespace ast {

class Program {
public:
    //TODO: change these to unordered maps instead of vectors. Then implement getFunction() in Program.cpp
    std::vector<std::shared_ptr<TypeDeclaration>> typeDecls; // Pointer to TypeDeclaration objects (global struct definitions)
    std::vector<std::shared_ptr<Declaration>> decls;     // Pointer to Declaration objects (pointer to global var declarations)
    std::vector<std::shared_ptr<Function>> funcs;        // Pointer to Function objects
    // Constructor
    Program();
    std::shared_ptr<Function> getFunction(const std::string &f);
};

} // namespace ast

#endif // PROGRAM_HPP

