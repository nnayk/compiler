#include "CfgProg.hpp"

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

