#include "CfgProg.hpp"
#include <utility>

CfgFunc::CfgFunc(std::string name,std::vector<ast::Declaration> params) : name(name), params(params) {}

std::shared_ptr<CfgFunc> CfgFunc::build(ast::Function &f) {
    //auto cfg_func = std::make_shared<CfgFunc>();  
    //auto cfg_func = std::shared_ptr<CfgFunc>(new CfgFunc(std::move(f.params),std::move(f.retType),std::move(f.locals),std::vector<Bblock>()));
    auto cfg_func = std::shared_ptr<CfgFunc>(new CfgFunc(f.name,std::move(f.params))); //,std::move(f.retType),std::move(f.locals),std::vector<Bblock>()));
    cfg_func->blocks = f.body->get_cfg();
	spdlog::debug("BUILT CFG FUNC {}", cfg_func->name);
    return cfg_func;
}

std::string CfgFunc::display() const {
	spdlog::debug("display: {}",this->name);
	return this->name;
}

