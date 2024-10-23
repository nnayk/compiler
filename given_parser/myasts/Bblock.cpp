#include "Bblock.hpp"

std::string Bblock::get_llvm() {
    spdlog::debug("inside Bblock::{}",__func__);
    std::string llvm_ir = "BBLOCK BODY";
    for(auto stmt:this->stmts) {
        llvm_ir += stmt->get_llvm();
    }
    return llvm_ir;
}
