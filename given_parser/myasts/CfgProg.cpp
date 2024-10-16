#include "CfgProg.hpp"

CfgProg::CfgProg(std::vector<std::shared_ptr<ast::TypeDeclaration>> typeDecls, std::vector<std::shared_ptr<ast::Declaration>> globals,std::vector<std::shared_ptr<CfgFunc>> funcs) : typeDecls(typeDecls),globals(globals), funcs(funcs) {}

std::shared_ptr<CfgProg> CfgProg::build(ast::Program &p) {
    auto cfg_prog = std::shared_ptr<CfgProg>(new CfgProg(p.typeDecls,p.decls,std::vector<std::shared_ptr<CfgFunc>>()));
    for( auto typeDecl : p.typeDecls ) {
        spdlog::debug("typeDecl LLVM IR = {}",typeDecl->get_llvm());
    }

    return cfg_prog;
}

