#include "CfgProg.hpp"
#include <utility>
#include <queue>
#include <cassert>
#include "Types.hpp"

std::string TAB="\t";
CfgFunc::CfgFunc(std::string name,std::vector<ast::Declaration> params, std::shared_ptr<ast::Type> retType, std::vector<ast::Declaration> locals) : name(name), params(params), retType(retType), locals(locals) {}

std::shared_ptr<CfgFunc> CfgFunc::build(ast::Function &f) {
    spdlog::info("inside CfgFunc::{}",__func__);
    //auto cfg_func = std::make_shared<CfgFunc>();  
    //auto cfg_func = std::shared_ptr<CfgFunc>(new CfgFunc(std::move(f.params),std::move(f.retType),std::move(f.locals),std::vector<Bblock>()));
    auto cfg_func = std::shared_ptr<CfgFunc>(new CfgFunc(f.name,std::move(f.params),std::move(f.retType),std::move(f.locals)));//,std::vector<Bblock>()));
    cfg_func->blocks = f.body->get_cfg();
    return cfg_func;
}

std::string CfgFunc::get_llvm() {
    spdlog::debug("inside CfgFunc::{}",__func__);
    if(dynamic_pointer_cast<ast::VoidType>(this->retType)) spdlog::debug("found void type!\n");
    if(dynamic_pointer_cast<ast::StructType>(this->retType)) spdlog::debug("found struct type!\n");
    this->retType->get_llvm();
    std::string llvm_ir = fmt::format("define noundef {} @{}(",this->retType->get_llvm(),this->name);
    //add params
    for (size_t i = 0; i < this->params.size(); ++i) {
		llvm_ir += this->params[i].get_llvm_init("param");
		if (i != this->params.size() - 1) {
			llvm_ir += ", ";
		}
	}  
    llvm_ir += ") ";
    llvm_ir += "{\n";
    // add local vars
    for (size_t i = 0; i < this->locals.size(); ++i) {
		llvm_ir += TAB+this->locals[i].get_llvm_init("local");
	}  
    //add LLVM IR for body
    if(this->blocks.size() > 0) {
        std::queue<std::shared_ptr<Bblock>> queue;
        queue.push(this->blocks[0]);
        while(!queue.empty()) {
            auto block = queue.front();
            queue.pop();
			spdlog::debug("popped block {}",*block);
            // TODO: change this check b/c can't print multiple times this way
            if(block->visited == 1) continue;
            llvm_ir += block->get_llvm();
            block->visited = 1;
			for(auto child : block->children) {
                spdlog::debug("pushing child {}",*child);
                queue.push(child);
            }
        }
    }
	llvm_ir += "}";
    return llvm_ir;
}

// BFS display of each block in the CFG
std::string CfgFunc::display() const {
    spdlog::debug("inside CfgFunc::{}",__func__);
	// number of bblocks from BFS walk of CFG. Purpose is to sanity check that
	// number of unique blocks in CFG = number of blocks in the list of blocks
	// for the CfgFunc
	int bfs_blocks = 0; 
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
            if(block->visited == 1) 
            {
                spdlog::debug("Already visited this blocks:{}\n",*block);
                continue;
            }
			bfs_blocks++;
            output += fmt::format("START OF BBLOCK #{}\n",bfs_blocks);
            output += fmt::format("{}",*block);
            output += fmt::format("END OF BBLOCK\n\n\n",bfs_blocks);
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
	// sanity check
    spdlog::debug("{} blocks seen in CFG, {} blocks in CfgFunc\n",bfs_blocks,this->blocks.size());
    assert(bfs_blocks==this->blocks.size());
    // mark the blocks unvisited 
    for(auto block : this->blocks) {
        block->visited = 0;
    }
	return output;
}

