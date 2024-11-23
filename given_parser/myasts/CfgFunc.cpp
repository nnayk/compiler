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
extern bool use_ssa;

CfgFunc::CfgFunc(std::string name,std::vector<ast::Declaration> params, std::shared_ptr<ast::Type> retType, std::vector<ast::Declaration> locals) : name(name), params(params), retType(retType), locals(locals) {
}

std::shared_ptr<CfgFunc> CfgFunc::build(ast::Function &f) {
    spdlog::info("inside CfgFunc::{}",__func__);
    //auto cfg_func = std::make_shared<CfgFunc>();  
    //auto cfg_func = std::shared_ptr<CfgFunc>(new CfgFunc(std::move(f.params),std::move(f.retType),std::move(f.locals),std::vector<Bblock>()));
    //Construct CFG
    auto cfg_func = std::shared_ptr<CfgFunc>(new CfgFunc(f.name,std::move(f.params),std::move(f.retType),std::move(f.locals)));//,std::vector<Bblock>()));
    cfg_func->return_block = std::make_shared<Bblock>();
    //cfg_func->return_block->label = Label::create("return");
    auto ret_expr = std::make_shared<ast::IdentifierExpression>(-1,"_ret");
    ret_expr->type = cfg_func->retType;
    auto ret_stmt = std::make_shared<ast::ReturnStatement>(-1,ret_expr);
    ret_stmt->final_return = true;
    ret_stmt->retType = cfg_func->retType;
    cfg_func->return_block->stmts.push_back(ret_stmt);
    cfg_func->return_block->final_return_block = true;
    cfg_func->blocks = f.body->get_cfg();
    cfg_func->blocks.push_back(cfg_func->return_block);
    spdlog::debug("FINAL return block = {}\n",*cfg_func->return_block);
    auto body_block = dynamic_pointer_cast<ast::BlockStatement>(f.body);
    for(auto block : body_block->return_bblocks) {
        spdlog::debug("adding parent to FINAL return block: {}\n",*block);
        block->children.push_back(cfg_func->return_block);
        cfg_func->return_block->parents.push_back(block);
    }
    spdlog::debug("CFG construction complete, gonna create labels for each block now!\n");
    // CFG construction done at this point, assign labels to each block
    cfg_func->create_labels();
    return cfg_func;
}

void CfgFunc::create_labels() {
    spdlog::debug("inside CfgFunc::{}\n",__func__);
    if(this->blocks.size() > 0) {
        std::stack<std::shared_ptr<Bblock>> stack;
        stack.push(this->blocks[0]);
        bool reverse_push = true;
        bool unvisited_parent = false;
        while(!stack.empty()) {
            reverse_push = true;
            unvisited_parent = false;
            auto block = stack.top();
            spdlog::debug("stack size = {}\n",stack.size());
            spdlog::debug("considering block {}\n",*block);
            // if there are unvisited parents then explore them first
            for(auto parent : block->parents) {
                if(!parent->visited && !block->is_loopback_parent(parent)) {
                    spdlog::debug("unvisited parent (no label) {}\n",*parent);
                    unvisited_parent = true;
                    stack.push(parent);
                }
            }
            if(unvisited_parent) continue;
            stack.pop();
			spdlog::debug("popped block {}",*block);
            // TODO: change this check b/c can't print multiple times this way
            if(block->visited == 1) {
                spdlog::debug("Yalready visited block {}\n",*block);
                continue;
            }
            // gen label here?
            block->label = Label::create();
            block->visited = 1;
            std::shared_ptr<ast::Statement> stmt = nullptr;
            auto num_stmts = block->stmts.size();
            if(num_stmts) {
                spdlog::debug("NOT a dummy block!\n");
            } else {
                spdlog::debug("dummy block!\n");
            }
            // if the block is a conditional (either a single conditional stmt or ends in a conditional then skip the llvm for the children as they would've already been handled by the if block  -- they should still be pushed however as in the case of an if w/non-empty then and non-empty else 
            if(reverse_push) {
				for (auto it = block->children.rbegin(); it != block->children.rend(); ++it) {
					std::cout << "LABEL pushing " << *it << " ";
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
    // mark each block as unvisited
    for(auto block : this->blocks) {
        block->visited = 0;
    }
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

    if(use_ssa) {
        llvm_ir += this->get_ssa();
    } else {
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
            bool unvisited_parent = false;
            while(!stack.empty()) {
                spdlog::debug("LLVM START OF WHILE LOOP\n");
                //skip_children_llvm = false;
                reverse_push = true;
                unvisited_parent = false;
                auto block = stack.top();
                spdlog::debug("LLVM considering block {}\n",block->label->getLabel());
                // if there are unvisited parents then explore them first
                for(auto parent : block->parents) {
                    if(!parent->visited && !block->is_loopback_parent(parent)) {
                        spdlog::debug("LLVM unvisited parent {}\n",*parent);
                        unvisited_parent = true;
                        stack.push(parent);
                    }
                }
                if(unvisited_parent) continue;
                stack.pop();
                spdlog::debug("LLVM popped block with label {}",block->label->getLabel());
                // TODO: change this check b/c can't print multiple times this way
                if(block->visited == 1) {
                    spdlog::debug("LLVM Yalready visited block {}\n",block->label->getLabel());
                    continue;
                }
                if(block->emit_llvm) {
                    auto block_label = block->label->getLabel();
                    spdlog::debug("LLVM gonna fetch llvm for block {}\n",block_label);
                    llvm_ir += block->get_llvm();
                    spdlog::debug("LLVM NOT skipping llvm for block with label {}: {}\n",block_label,*block);
                } else {
                    spdlog::debug("skipping llvm for block {}\n",block->label->getLabel());
                }
                block->visited = 1;
                std::shared_ptr<ast::Statement> stmt = nullptr;
                auto num_stmts = block->stmts.size();
                if(num_stmts) {
                    spdlog::debug("not a dummy block!\n");
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
    }
    llvm_ir += "}\n";
    return llvm_ir;
}

std::string CfgFunc::get_ssa() {
    spdlog::debug("inside CfgFunc::{}\n",__func__);
    std::string ssa = "";
    std::string block_label = "";
    std::vector<std::shared_ptr<Bblock>> unsealed_blocks;
    auto head_block = blocks[0];
    // Step 0: Add param entries to L0
    head_block->add_initial_mapping(this->params);
    spdlog::debug("HEAD BLOCK MAPPING: {}\n",*head_block->ssa_map);
    spdlog::debug("Done with initial mapping!\n");
    // Step 1: Resolve var defs+uses for each statement in the block
    for(auto block : this->blocks) {
        spdlog::debug("resolving bblock {} defs+uses\n",block->label->getLabel());
        block->resolve_def_uses();
    }
    //return ssa;
    // Step 2: Fill unsealed blocks (as their loopback parents are now safe to consider)
    // Step 3: Remove non-trivial phis
    // Step 4: Generate ssa ssa
    //add ssa IR for body
    if(this->blocks.size() > 0) {
        std::stack<std::shared_ptr<Bblock>> stack;
        stack.push(this->blocks[0]);
        bool reverse_push = true;
        bool unvisited_parent = false;
        while(!stack.empty()) {
            spdlog::debug("SSA START OF WHILE LOOP\n");
            reverse_push = true;
            unvisited_parent = false;
            auto block = stack.top();
            spdlog::debug("SSA considering block {}\n",block->label->getLabel());
            // if there are unvisited parents then explore them first
            for(auto parent : block->parents) {
                if(!parent->visited && !block->is_loopback_parent(parent)) {
                    spdlog::debug("SSA unvisited parent {}\n",*parent);
                    unvisited_parent = true;
                    stack.push(parent);
                }
            }
            if(unvisited_parent) continue;
            stack.pop();
			spdlog::debug("ssa popped block with label {}",block->label->getLabel());
            // TODO: change this check b/c can't print multiple times this way
            if(block->visited == 1) {
                spdlog::debug("ssa Yalready visited block {}\n",block->label->getLabel());
                continue;
            }
            if(block->emit_llvm) {
                auto block_label = block->label->getLabel();
                spdlog::debug("ssa gonna fetch ssa for block {}\n",block_label);
                ssa += block->get_ssa();
                spdlog::debug("ssa NOT skipping ssa for block with label {}: {}\n",block_label,*block);
            } else {
                spdlog::debug("skipping ssa for block {}\n",block->label->getLabel());
            }
            block->visited = 1;
            std::shared_ptr<ast::Statement> stmt = nullptr;
            auto num_stmts = block->stmts.size();
            if(num_stmts) {
                spdlog::debug("not a dummy block!\n");
            } else {
                spdlog::debug("dummy block!\n");
            }
            // if the block is a conditional (either a single conditional stmt or ends in a conditional then skip the ssa for the children as they would've already been handled by the if block  -- they should still be pushed however as in the case of an if w/non-empty then and non-empty else 
            if(reverse_push) {
				for (auto it = block->children.rbegin(); it != block->children.rend(); ++it) {
					std::cout << *it << " ";
                    //spdlog::debug("pushing *it {}",*it);
                    stack.push(*it);
				}
            } else {
                for(auto child : block->children) {
                    spdlog::debug("pushing child {}",*child);
                    //if(skip_children_ssa) child->emit_ssa = false;
                    stack.push(child);
                }
            }
        }
    }
    // TODO: Run optimizations on post-LLVM CFG 
    return ssa;
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
			spdlog::debug("CfgFunc popped block with label {}",block->label->getLabel());
            //spdlog::debug("{}\n",*block);
            spdlog::debug("yay block {} popped, has it been visited? {}\n",block->label->getLabel(),block->visited);
            // TODO: change this check b/c can't print multiple times this way
            if(block->visited == 1) 
            {
                spdlog::debug("Already visited this block: {}\n",block->label->getLabel());
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
    //URGENT: uncomment this!
    //assert(bfs_blocks==this->blocks.size());
    // mark the blocks unvisited 
    for(auto block : this->blocks) {
        block->visited = 0;
    }
	return output;
}

std::string CfgFunc::get_asm() {
    spdlog::debug("inside CfgFunc::{}\n",__func__);
    this->get_llvm();
    // TODO: Run optimizations on post-LLVM CFG
    std::string arm = fmt::format(".global {}\n",this->name);
	arm += fmt::format("{}:\n",this->name);
    // Add prologue
	// Step 1: Calculate sp adjustment based on # of local vars (Even if 0 local vars are present still we must push the fp + lr onto stack...note technically if the function doesn't make any invocations then this is unneeded but I don't want to deal with that for now so just gonna save/restore fp+lr)
	auto sp_adjustment = (this->locals.size()+2)*16; // +2 for fp + lr
	arm += fmt::format("stp fp, lr [sp,-{}] !\n",sp_adjustment);
	// Step 2: Save callee saved regs? idt this will be needed for this program tbh
	// Step 3: Perfom modified DFS to translate each line in each block
	if(this->blocks.size() > 0) {
		std::stack<std::shared_ptr<Bblock>> stack;
		stack.push(this->blocks[0]);
		bool unvisited_parent = false;
		while(!stack.empty()) {
			spdlog::debug("ARM START OF WHILE LOOP\n");
			//skip_children_llvm = false;
			unvisited_parent = false;
			auto block = stack.top();
			spdlog::debug("ARM considering block {}\n",block->label->getLabel());
			// if there are unvisited parents then explore them first
			for(auto parent : block->parents) {
				if(!parent->visited && !block->is_loopback_parent(parent)) {
					spdlog::debug("ARM unvisited parent {}\n",*parent);
					unvisited_parent = true;
					stack.push(parent);
				}
			}
			if(unvisited_parent) continue;
			stack.pop();
			spdlog::debug("ARM popped block with label {}",block->label->getLabel());
			// TODO: change this check b/c can't print multiple times this way
			if(block->visited == 1) {
				spdlog::debug("ARM Yalready visited block {}\n",block->label->getLabel());
				continue;
			}
			auto block_label = block->label->getLabel();
			spdlog::debug("ARM gonna fetch arm for block {}\n",block_label);
			arm += block->get_arm();
			block->visited = 1;
			std::shared_ptr<ast::Statement> stmt = nullptr;
			auto num_stmts = block->stmts.size();
			if(num_stmts) {
				spdlog::debug("not a dummy block!\n");
			} else {
				spdlog::debug("dummy block!\n");
			}
			for (auto it = block->children.rbegin(); it != block->children.rend(); ++it) {
				std::cout << *it << " ";
				stack.push(*it);
			}
		}
	}
	
    // Add epilogue
	arm += fmt::format("ldp fp, lr [sp], {}\n",sp_adjustment);	
    return arm;
}

