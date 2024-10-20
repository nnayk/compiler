#include "CfgProg.hpp"
#include <utility>
#include <queue>

CfgFunc::CfgFunc(std::string name,std::vector<ast::Declaration> params, std::shared_ptr<ast::Type> retType, std::vector<ast::Declaration> locals) : name(name), params(params), retType(retType), locals(locals) {}

std::shared_ptr<CfgFunc> CfgFunc::build(ast::Function &f) {
    spdlog::info("inside CfgFunc::{}",__func__);
    //auto cfg_func = std::make_shared<CfgFunc>();  
    //auto cfg_func = std::shared_ptr<CfgFunc>(new CfgFunc(std::move(f.params),std::move(f.retType),std::move(f.locals),std::vector<Bblock>()));
    auto cfg_func = std::shared_ptr<CfgFunc>(new CfgFunc(f.name,std::move(f.params),std::move(f.retType),std::move(f.locals)));//,std::vector<Bblock>()));
    cfg_func->blocks = f.body->get_cfg();
    return cfg_func;
}

// BFS display of each block in the CFG
std::string CfgFunc::display() const {
    spdlog::debug("inside CfgFunc::{}",__func__);
	auto output = fmt::format("{} (ret type = {}): \n",this->name,*this->retType);
    output += fmt::format("PARAMS:\n");
	for(auto param : this->params) {
		output += fmt::format("{}",param);
	}
	output += fmt::format("\n");	
    output += fmt::format("LOCALS:\n");
	for(auto local : this->locals) {
		output += fmt::format("{}",local);
	}
    output += fmt::format("BODY:\n");
    if(this->blocks.size() > 0) {
        std::queue<std::shared_ptr<Bblock>> queue;
        queue.push(this->blocks[0]);
        while(!queue.empty()) {
            auto block = queue.front();
            queue.pop();
			spdlog::debug("popped block {}",*block);
            // TODO: change this check b/c can't print multiple times this way
            if(block->visited == 1) continue;
            output += fmt::format("START OF BBLOCK\n");
            output += fmt::format("{}",*block);
            output += fmt::format("END OF BBLOCK\n\n\n");
            block->visited = 1;
			for(auto child : block->children) {
                spdlog::debug("pushing child {}",*child);
                queue.push(child);
            }
        }
    } else {
        output += fmt::format("No basic blocks, empty function body!\n");
    }
	output += fmt::format("END OF CFG FOR {}\n",this->name);	
	return output;
}

