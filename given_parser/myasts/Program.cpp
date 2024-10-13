#include "Program.hpp"

namespace ast{
    // Constructor implementation that creates empty lists
    Program::Program() : typeDecls(), decls(), funcs() {}

    //TODO
    std::shared_ptr<Function> Program::getFunction(const std::string &f) {
        return nullptr;
    }
}
