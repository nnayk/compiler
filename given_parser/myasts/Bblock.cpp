#include "Bblock.hpp"

std::string Bblock::get_llvm() {
    std::string llvm_ir;
    spdlog::debug("inside Bblock::{}",__func__);
    for(auto stmt:this->stmts) {
        spdlog::debug("Invoking get_llvm() for {}\n",*stmt);
        llvm_ir += stmt->get_llvm();
    }
    return llvm_ir;
}
