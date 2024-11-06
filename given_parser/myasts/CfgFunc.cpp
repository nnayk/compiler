#include "CfgProg.hpp"
#include <utility>
#include <queue>
#include <stack>
#include <cassert>
#include "Types.hpp"
#include "ConditionalStatement.hpp"
#include "ReturnStatement.hpp"
#include "BlockStatement.hpp"
#include "IdentifierExpression.hpp"
#include "Label.hpp"

std::string TAB="\t";
CfgFunc::CfgFunc(std::string name,std::vector<ast::Declaration> params, std::shared_ptr<ast::Type> retType, std::vector<ast::Declaration> locals) : name(name), params(params), retType(retType), locals(locals) {
}

std::shared_ptr<CfgFunc> CfgFunc::build(ast::Function &f) {
    spdlog::info("inside CfgFunc::{}",__func__);
    //auto cfg_func = std::make_shared<CfgFunc>();  
    //auto cfg_func = std::shared_ptr<CfgFunc>(new CfgFunc(std::move(f.params),std::move(f.retType),std::move(f.locals),std::vector<Bblock>()));
    auto cfg_func = std::shared_ptr<CfgFunc>(new CfgFunc(f.name,std::move(f.params),std::move(f.retType),std::move(f.locals)));//,std::vector<Bblock>()));
    cfg_func->return_block = std::make_shared<Bblock>();
    cfg_func->return_block->label = Label::create("return");
    auto ret_expr = std::make_shared<ast::IdentifierExpression>(-1,"_ret");
    ret_expr->type = cfg_func->retType;
    auto ret_stmt = std::make_shared<ast::ReturnStatement>(-1,ret_expr);
    ret_stmt->final_return = true;
    ret_stmt->retType = cfg_func->retType;
    cfg_func->return_block->stmts.push_back(ret_stmt);
    cfg_func->blocks = f.body->get_cfg();
    cfg_func->blocks.push_back(cfg_func->return_block);
    spdlog::debug("FINAL return block = {}\n",*cfg_func->return_block);
    auto body_block = dynamic_pointer_cast<ast::BlockStatement>(f.body);
    for(auto block : body_block->return_bblocks) {
        spdlog::debug("adding parent to FINAL return block: {}\n",*block);
        block->children.push_back(cfg_func->return_block);
        cfg_func->return_block->parents.push_back(block);
    }
    return cfg_func;
}

std::string CfgFunc::get_llvm() {
    spdlog::debug("inside CfgFunc::{}\n",__func__);
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
        std::stack<std::shared_ptr<Bblock>> stack;
        stack.push(this->blocks[0]);
        //bool skip_children_llvm = false;
        bool reverse_push = true;
        while(!stack.empty()) {
            //skip_children_llvm = false;
            reverse_push = true;
            auto block = stack.top();
            stack.pop();
			spdlog::debug("popped block {}",*block);
            // TODO: change this check b/c can't print multiple times this way
            if(block->visited == 1) {
                spdlog::debug("Yalready visited block {}\n",*block);
                continue;
            }
            if(block->emit_llvm) {
                llvm_ir += block->get_llvm();
                spdlog::debug("NOT skipping llvm for block {}\n",*block);
            } else {
                spdlog::debug("skipping llvm for block {}\n",*block);
            }
            block->visited = 1;
            std::shared_ptr<ast::Statement> stmt = nullptr;
            auto num_stmts = block->stmts.size();
            if(num_stmts) {
                stmt = block->stmts[num_stmts-1];
                if(auto cond_stmt =  dynamic_pointer_cast<ast::ConditionalStatement>(stmt)) {
                    // Recall both then and else stmts cannot be null b/c
                    // BlockStatement::get_llvm() would've just ignored this
                    // Conditional statement
                    if((cond_stmt->thenLabel == cond_stmt->afterLabel) ) {
                        spdlog::debug("not reverse pushing for cond_stmt {}\n");//,*cond_stmt);
                        reverse_push = false;
                    }
                    //spdlog::debug("skipping children llvm due to conditional stmt {}\n",*stmt);
                    //skip_children_llvm = true;
                }
            } else {
                spdlog::debug("dummy block!\n");
            }
            // if the block is a conditional (either a single conditional stmt or ends in a conditional then skip the llvm for the children as they would've already been handled by the if block  -- they should still be pushed however as in the case of an if w/non-empty then and non-empty else 
            if(reverse_push) {
				for (auto it = block->children.rbegin(); it != block->children.rend(); ++it) {
					std::cout << *it << " ";
                    //spdlog::debug("pushing *it {}",*it);
                    stack.push(*it);
				}
            } else {
                for(auto child : block->children) {
                    spdlog::debug("pushing child {}",*child);
                    //if(skip_children_llvm) child->emit_llvm = false;
                    stack.push(child);
                }
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
            spdlog::debug("yay block visited: {}\n",block->visited);
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
    spdlog::debug("output cfg={}\n",output);
	// sanity check
    spdlog::debug("{} blocks seen in CFG, {} blocks in CfgFunc\n",bfs_blocks,this->blocks.size());
    assert(bfs_blocks==this->blocks.size());
    // mark the blocks unvisited 
    for(auto block : this->blocks) {
        block->visited = 0;
    }
	return output;
}

