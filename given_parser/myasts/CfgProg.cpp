#include "CfgProg.hpp"
#include <queue>
CfgProg::CfgProg(std::vector<std::shared_ptr<ast::TypeDeclaration>> typeDecls, std::vector<std::shared_ptr<ast::Declaration>> globals,std::vector<std::shared_ptr<CfgFunc>> funcs) : typeDecls(typeDecls),globals(globals), funcs(funcs) {}

std::shared_ptr<CfgProg> CfgProg::build(ast::Program &p) {
    spdlog::info("inside CfgProg::{}",__func__);
    auto cfg_prog = std::shared_ptr<CfgProg>(new CfgProg(p.typeDecls,p.decls,std::vector<std::shared_ptr<CfgFunc>>()));
    // just simple testing, delete later
    for( auto typeDecl : p.typeDecls ) {
        spdlog::debug("typeDecl LLVM IR = {}",typeDecl->get_llvm());
    }
    // Walk each function and generate the Cfg (specifically the CfgFunc object)
    for( auto func : p.funcs) {
        spdlog::debug("Gonna build CFG for function {}",func->name);
        cfg_prog->funcs.push_back(CfgFunc::build(*func));
    }
    return cfg_prog;
}

std::string CfgProg::get_llvm() {
    std::string llvm_ir = "";
    // Generate the LLVM for each struct
    for(auto typeDecl : this->typeDecls) {
        llvm_ir += fmt::format("{}\n",typeDecl->get_llvm_init());        
    }
    llvm_ir += "\n";
    // Get the LLVM for each global
    for(auto global : this->globals) {
        llvm_ir += fmt::format("{}\n",global->get_llvm_init("global"));        
    }
    llvm_ir += "\n";
    // Get the LLVM for each function
    // Walk the CFG (BFS) and get the LLVM IR for each bblock
    for(auto func : this->funcs) {
        llvm_ir += fmt::format("{}\n",func->get_llvm());
    }
    
    return llvm_ir;
}

std::string CfgProg::get_asm() {
    spdlog::debug("inside CfgProg::{}\n",__func__);
    std::string arm = ".data\n";
    arm += "fmt: .asciz \"%d\\n\"\n";
    arm += "fmtn: .asciz \"%d\\n\"\n";
    arm += "fp .req x29\nlr .req x30\n\n\n";
    arm += ".arch armv8-a\n\n\n";
    arm += ".text\n";
    // TODO: add bss section
    for(auto func : this->funcs) {
        arm += fmt::format("{}\n",func->get_asm());
    }
    return arm;
}

