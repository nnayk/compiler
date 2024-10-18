#include "CfgProg.hpp"
#include <utility>

CfgFunc::CfgFunc(std::string name,std::vector<ast::Declaration> params, std::shared_ptr<ast::Type> retType, std::vector<ast::Declaration> locals) : name(name), params(params), retType(retType), locals(locals) {}

std::shared_ptr<CfgFunc> CfgFunc::build(ast::Function &f) {
    //auto cfg_func = std::make_shared<CfgFunc>();  
    //auto cfg_func = std::shared_ptr<CfgFunc>(new CfgFunc(std::move(f.params),std::move(f.retType),std::move(f.locals),std::vector<Bblock>()));
    auto cfg_func = std::shared_ptr<CfgFunc>(new CfgFunc(f.name,std::move(f.params),std::move(f.retType),std::move(f.locals)));//,std::vector<Bblock>()));
    cfg_func->blocks = f.body->get_cfg();
    return cfg_func;
}

std::string CfgFunc::display() const {
	auto output = fmt::format("{} (ret type = {}): \n",this->name,*this->retType);
	for(auto param : this->params) {
		output += fmt::format("{}",param);
	}
	output += fmt::format("\n");	
	for(auto local : this->locals) {
		output += fmt::format("{}",local);
	}
	output += fmt::format("\n");	
	for(auto block : this->blocks) {
		output += fmt::format("{}",*block);
	}
	output += fmt::format("\n");	
	return output;
}

