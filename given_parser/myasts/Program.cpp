#include "Program.hpp"
#include "TypeException.hpp"
#include <algorithm>
namespace ast{
    // Constructor implementation that creates empty lists
    Program::Program() : typeDecls(), decls(), funcs() {}

    //TODO
    std::shared_ptr<Function> Program::getFunction(const std::string &f) {
        spdlog::debug("inside Program::{}\n",__func__);
        auto it = std::find_if(funcs.begin(),funcs.end(),[&f](const std::shared_ptr<ast::Function>& func) {
            return func->getName() == f; // Assuming Function has a getName() method
        });
        if (it == funcs.end()) {
			throw TypeException(fmt::format("Attempt to invoke nonexistent functi on {}\n",f));
        }
        return *it;
    }
}
