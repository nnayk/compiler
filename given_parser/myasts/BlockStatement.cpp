#include "BlockStatement.hpp"
#include "ConditionalStatement.hpp" // used during cfg construction
#include "WhileStatement.hpp" // used during cfg construction
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
        if(prev_stmt) spdlog::debug("prev_stmt = {}\n",*prev_stmt);
        spdlog::debug("stmt = {}\n",*stmt);
        spdlog::debug("BlockStatement:Gonna build cfg for stmt {}",*stmt);
        auto new_blocks = stmt->get_cfg();
        spdlog::debug("BlockStatement:Done building cfg for stmt. size of new blocks = {}",new_blocks.size());
        auto new_head = new_blocks[0];
        spdlog::debug("new head has {} stmts: {}\n",new_head->stmts.size(),*new_head);
        //assert(new_head->stmts.size()==1);
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
            std::string err = "Probably a while conditional stmt (see WhileStatement::get_cfg";
            assert(dummy_block->stmts.size()==0 && err.c_str());
            for(auto parent : dummy_block->parents) {
				spdlog::debug("Looking at dummy parent {}\n",*parent);
				assert(0 <= parent->children.size() && parent->children.size() <= 2);
				if(parent->children[0] == dummy_block) {
                    spdlog::debug("Replacing dummy child (first child)\n");
					parent->children[0] = new_head;
				} else {
                    spdlog::debug("Replacing dummy child (second child)\n");
					parent->children[1] = new_head;
				}
            	new_head->parents.push_back(parent);
			}
            // remove the dummy bblock from the list of bblocks
            spdlog::debug("Removing the dummy bblock from the list of bblocks");
            blocks.erase(std::remove(blocks.begin(),blocks.end(),dummy_block),blocks.end()); 
        } else if(prev_tail) {
            // TODO: if curr stmt not an if or while stmt then merge it into
            // prev_tail's BBlock stmts vector instead of keeping it as a separate
            // child block
            // Add after block
            // URGENT: replace these 2 lines w/an addEdge method
            prev_tail->children.push_back(new_head);
            new_head->parents.push_back(prev_tail);
            if(dynamic_pointer_cast<ast::WhileStatement>(prev_stmt)) {
                assert(prev_blocks.size()==1);
                auto prev_head = prev_blocks[0];
                spdlog::debug("prev_head = {}\n",*prev_head);
                //assert(prev_head->parents.size() == 1);
                for(auto parent : prev_head->parents) {
                    auto cond_parent = dynamic_pointer_cast<ConditionalStatement>(parent->stmts[parent->stmts.size()-1]);
                    assert(cond_parent);
                    cond_parent->elseBlock = stmt;
                    //encountered self loop
                    if(parent==prev_tail) {
                        continue;    
                    }
                    spdlog::debug("Looking at parent {}\n",*parent);
                    //assert(0 <= parent->children.size() && parent->children.size() <= 2);
                    parent->children.push_back(new_head);
                    new_head->parents.push_back(parent);
                    spdlog::debug("parent now = {}\n",*parent);
                    spdlog::debug("new_head now = {}\n",*new_head);
                }
            // TODO: merge blocks together
            } else if(!dynamic_pointer_cast<ast::WhileStatement>(prev_stmt) && !dynamic_pointer_cast<ast::WhileStatement>(stmt)) {
                // remove the unneeded parent child relationship
                prev_tail->children.pop_back();
                new_head->parents.pop_back();
                assert(prev_tail->children.size()==0);
                assert(new_head->parents.size()==0);
                prev_tail->stmts.push_back(stmt);
                new_blocks.erase(new_blocks.begin());
                spdlog::debug("Removed new_head={} from new_blocks, now new_blocks size = {}\n",*new_head,new_blocks.size());
                if(auto cond_stmt = dynamic_pointer_cast<ast::ConditionalStatement>(stmt)) {
                    for(auto child : new_head->children) {
                        prev_tail->children.push_back(child);
                        blocks.erase(std::remove(blocks.begin(),blocks.end(),new_head),blocks.end()); 
                        // Remove the "temp" if block parent which is now obsolete
                        child->parents.erase(std::remove(child->parents.begin(),child->parents.end(),new_head),child->parents.end());
                        child->parents.push_back(prev_tail);
                    }
                }
            }
        }
        if(dynamic_pointer_cast<ast::WhileStatement>(stmt)) {
            // add self loop (then case)
            auto new_tail = new_blocks[new_blocks.size()-1];
            spdlog::debug("new tail = {}\n",*new_tail);
            new_tail->children.push_back(new_head);
            new_head->parents.push_back(new_tail);
            spdlog::debug("now new tail = {}\n",*new_tail);
            //TODO: append guard (condition) stmt to prev_tail as an if statement. if prev tail is null then make a new block to represent cond as prev_tail AND make prev_tail the parent of new_head since this would not have been done already. this must occur before the self loop is added with new head in order to guarantee that parents[0] is the previous block (or else it'll be the new_head)
            auto cond_stmt = std::make_shared<ConditionalStatement>(stmt->getLineNum(),static_pointer_cast<WhileStatement>(stmt)->get_guard(),stmt,nullptr);
            if(prev_tail) {
                for(auto parent : new_head->parents) {
                    if(parent==new_tail) continue;
                    parent->stmts.push_back(cond_stmt);
                }
            } else {
                auto temp = cond_stmt->get_cfg();
                std::string err = "This is a makeshift cond stmt that only should contain the while cond stmt -- why is there >1 block???";
                prev_tail = temp[0];
                assert(prev_tail->children.size()==1); 
                blocks.push_back(prev_tail);
                // set the then block to the current while block
                prev_tail->children[0] = new_head; 
                new_head->parents.push_back(prev_tail);
            }
        }
        // TODO: once bblock merging is done (see above TODO) these will have
        // to be tweaked
        prev_stmt = stmt;
        spdlog::debug("prev_stmt = {}, stmt = {}\n",*prev_stmt,*stmt);
        if(new_blocks.size()) {
            prev_blocks = new_blocks; 
            prev_tail = new_blocks[new_blocks.size()-1];
        }
        spdlog::debug("prev_tail = {}\n",*prev_tail);
        spdlog::debug("before total # of blocks = {}, adding {} blocks\n",blocks.size(),new_blocks.size());
        blocks.insert(blocks.end(),new_blocks.begin(),new_blocks.end());
        spdlog::debug("after total # of blocks = {}, added {} blocks\n",blocks.size(),new_blocks.size());
    }
    spdlog::debug("FINAL # of blocks = {}\n",blocks.size());
    return blocks;
}

// TODO: delete this as I think bblocks won't have block statements
std::string BlockStatement::get_llvm() { 
	spdlog::debug("inside BlockStatement::{}\n",__func__);
	//std::string llvm_ir="BlockStatement\n";
    std::string llvm_ir = "";
    for(auto stmt : this->statements) {
        llvm_ir += stmt->get_llvm();
    }
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
