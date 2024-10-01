#include "Program.hpp"

namespace ast{
    // Constructor implementation that creates empty lists
    Program::Program() : types(), decls(), funcs() {}

    // Destructor implementation to clean up dynamically allocated memory
    Program::~Program() {
        for (TypeDeclaration* type : types) {
            delete type;
        }

        for (Declaration* decl : decls) {
            delete decl;
        }

        for (Function* func : funcs) {
            delete func;
        }
    }
}
