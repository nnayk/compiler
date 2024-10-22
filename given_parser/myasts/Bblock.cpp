#include "Bblock.hpp"

std::string Bblock::get_llvm() {
    std::string llvm_ir = "";
    for(auto stmt:this->stmts) {
        llvm_ir += stmt->get_llvm();
    }
}
