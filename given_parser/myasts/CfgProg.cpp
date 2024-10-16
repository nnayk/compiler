#include "CfgProg.hpp"

CfgProg::CfgProg(std::vector<std::shared_ptr<ast::TypeDeclaration>> typeDecls, std::vector<std::shared_ptr<ast::Declaration>> globals,std::vector<std::shared_ptr<CfgFunc>> funcs) : typeDecls(typeDecls),globals(globals), funcs(funcs) {}

std::shared_ptr<CfgProg> CfgProg::build(ast::Program &p) {
    auto cfg_func = std::shared_ptr<CfgProg>(new CfgProg(std::vector<std::shared_ptr<ast::TypeDeclaration>>(), std::vector<std::shared_ptr<ast::Declaration>>(),std::vector<std::shared_ptr<CfgFunc>>()));
    return nullptr;
}

