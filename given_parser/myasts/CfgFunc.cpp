#include "CfgProg.hpp"
#include <utility>

CfgFunc::CfgFunc(std::vector<ast::Declaration> params) : params(params) {}

std::shared_ptr<CfgFunc> CfgFunc::build(ast::Function &f) {
    //auto cfg_func = std::make_shared<CfgFunc>();  
    //auto cfg_func = std::shared_ptr<CfgFunc>(new CfgFunc(std::move(f.params),std::move(f.retType),std::move(f.locals),std::vector<Bblock>()));
    auto cfg_func = std::shared_ptr<CfgFunc>(new CfgFunc(std::move(f.params))); //,std::move(f.retType),std::move(f.locals),std::vector<Bblock>()));
    //cfg_func->blocks = std::move(f.body->get_cfg());
    return cfg_func;
}


