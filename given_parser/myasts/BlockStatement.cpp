#include "BlockStatement.hpp"
#include "ConditionalStatement.hpp" // used during cfg construction
#include <cassert>

namespace ast {

// Constructor implementation
BlockStatement::BlockStatement(int lineNum, const std::vector<std::shared_ptr<Statement>>& statements)
    : AbstractStatement(lineNum), statements(statements) {}

void BlockStatement::typecheck(Env &env) {
    spdlog::info("inside BlockStatement::{}\n",__func__);
    for(auto &stmt:statements) {
        stmt->typecheck(env);
    }
}

std::vector<std::shared_ptr<Bblock>> BlockStatement::get_cfg() {
    spdlog::info("inside BlockStatement::{}\n",__func__);
    // only one block will be created but have to return a vector for 
    // compatability with the get_cfg Statement wide definitin
    auto blocks = std::vector<std::shared_ptr<Bblock>>();
    std::shared_ptr<Bblock> prev_tail = nullptr;
    std::vector<std::shared_ptr<Bblock>> prev_blocks;
    std::shared_ptr<Statement> prev_stmt = nullptr;
    spdlog::debug("{} stmts to process",this->statements.size());
    for(auto stmt : this->statements) {
        spdlog::debug("BlockStatement:Gonna build cfg for stmt {}",*stmt);
        auto new_blocks = stmt->get_cfg();
        spdlog::debug("BlockStatement:Done building cfg for stmt. size of new blocks = {}",new_blocks.size());
        auto new_head = new_blocks[0];
        //w/o this check the dummy will remain...just test this works as expected
        //for now
        // if the previous block stmt was a conditional, then replace its
        // outbound dummy block with this current block
        if(dynamic_pointer_cast<ast::ConditionalStatement>(prev_stmt)) {
			spdlog::debug("Replacing trailing dummy block for conditional on line {}\n",prev_stmt->getLineNum());
            // Replace the trailing dummy node from the if block with current block.
            // The dummy block should always be the last block in the mini-CFG for
            // an if statement
            auto dummy_block = prev_tail; 
			spdlog::debug("deleting dummy block with {} parents: {}\n", dummy_block->parents.size(),*dummy_block);
			// TODO: assert it's a dummy block
            for(auto parent : dummy_block->parents) {
				spdlog::debug("Looking at parent {}\n",*parent);
				//assert(0 <= parent->children.size() && parent->children.size() <= 2);
				if(parent->children[0] == dummy_block) {
					parent->children[0] = new_head;
				} else {
					parent->children[1] = new_head;
				}
            	new_head->parents.push_back(parent);
			}
            // remove the dummy bblock from the list of bblocks
            spdlog::debug("Removing the dummy bblock from the list of bblocks");
            blocks.erase(std::remove(blocks.begin(),blocks.end(),dummy_block),blocks.end()); 
        } else if(prev_tail) {
            prev_tail->children.push_back(new_head);
            new_head->parents.push_back(prev_tail);
        }
        prev_stmt = stmt;
        prev_blocks = new_blocks;
        prev_tail = new_blocks[new_blocks.size()-1];
        spdlog::debug("prev_tail = {}\n",*prev_tail);
        blocks.insert(blocks.end(),new_blocks.begin(),new_blocks.end());
    }
    return blocks;
}

// TODO: delete this as I think bblocks won't have block statements
std::string BlockStatement::get_llvm() { 
	spdlog::debug("inside BlockStatement::{}\n",__func__);
	std::string llvm_ir="BlockStatement\n";
	return llvm_ir;
} 

/*
std::vector<std::shared_ptr<Bblock>> BlockStatement::get_cfg() {
    // only one block will be created but have to return a vector for 
    // compatability with the get_cfg Statement wide definitin
    auto blocks = std::vector<std::shared_ptr<Bblock>>();
    auto block = std::make_shared<Bblock>();
    block->stmts.push_back(std::shared_from_this());
    blocks.push_back(block);
    return blocks;
}
*/

} // namespace ast

