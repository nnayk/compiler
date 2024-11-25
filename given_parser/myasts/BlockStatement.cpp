#include "BlockStatement.hpp"
#include "ConditionalStatement.hpp" // used during cfg construction
#include "WhileStatement.hpp" // used during cfg construction
#include "ReturnStatement.hpp" // used during cfg construction
#include "AssignmentStatement.hpp" // used during cfg construction
#include <cassert>

namespace ast {

// Constructor implementation
BlockStatement::BlockStatement(int lineNum, const std::vector<std::shared_ptr<Statement>>& statements)
    : AbstractStatement(lineNum), statements(statements) {}

void BlockStatement::typecheck(Env &env, Function &f) {
    spdlog::info("inside BlockStatement::{}\n",__func__);
    for(auto &stmt:statements) {
        stmt->typecheck(env,f);
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
    bool is_while_stmt, is_ret_stmt, prev_cond_stmt, prev_ret_stmt, is_cond_stmt;
    for(auto stmt : this->statements) {
        prev_ret_stmt = dynamic_pointer_cast<ReturnStatement>(prev_stmt) != nullptr;
        //prev_while_stmt = dynamic_pointer_cast<WhileStatement>(prev_stmt) != nullptr;
        prev_cond_stmt = dynamic_pointer_cast<ConditionalStatement>(prev_stmt) != nullptr;
        is_ret_stmt = dynamic_pointer_cast<ReturnStatement>(stmt) != nullptr;
        is_while_stmt = dynamic_pointer_cast<WhileStatement>(stmt) != nullptr;
        is_cond_stmt = dynamic_pointer_cast<ast::ConditionalStatement>(stmt) != nullptr;
        auto new_blocks = stmt->get_cfg();
        auto new_head = new_blocks[0];
        if(prev_stmt) spdlog::debug("prev_stmt = {}\n",*prev_stmt);
        spdlog::debug("stmt = {}\n",*stmt);
        spdlog::debug("BlockStatement:Gonna build cfg for stmt {}",*stmt);
        if(is_ret_stmt) {
            stmt = new_blocks[0]->stmts[0];
            assert(dynamic_pointer_cast<AssignmentStatement>(stmt));
        } else if(is_while_stmt) {
            spdlog::debug("found while stmt, gonna treat it as a cond!\n");
            auto cond_stmt = new_blocks[0]->stmts[0];
            assert(dynamic_pointer_cast<ConditionalStatement>(cond_stmt));
            spdlog::debug("Re-assigning while stmt {}\n to cond stmt {}\n",*stmt,*cond_stmt);
            stmt = cond_stmt;
        }
        spdlog::debug("BlockStatement:Done building cfg for stmt. size of new blocks = {}",new_blocks.size());
        if(is_ret_stmt) {
            auto ret_block = new_head;
            // if we're gonna merge this block with prev then add prev_tail to the list of return block.
            // The cases we won't merge is if prev_tail is an if (we'll just replace the dummy then with 
            // curr block) or if prev_stmt was a while. TODO: make a boolean "merge" that tells whether to merge prev and curr or not
            //if(prev_tail && !prev_while_stmt && !prev_cond_stmt) ret_block = prev_tail;
            if(prev_tail && !prev_cond_stmt) ret_block = prev_tail;
            spdlog::debug("adding return stmt to list of ret blocks:{}\n",*ret_block);
            this->return_bblocks.insert(ret_block);
        }
        spdlog::debug("new head has {} stmts: {}\n",new_head->stmts.size(),*new_head);
        assert(!new_head->visited);
        //assert(new_head->stmts.size()==1);
        //w/o this check the dummy will remain...just test this works as expected
        //for now
        if(prev_ret_stmt) {
            spdlog::debug("prev block was a return block, no merging! prev_stmt = {}\n",*prev_stmt);
        } else if(dynamic_pointer_cast<ast::ConditionalStatement>(prev_stmt)) {
        // if the previous block stmt was a conditional, then replace its
        // outbound dummy block with this current block
			spdlog::debug("Replacing trailing dummy block for conditional on line {}\n",prev_stmt->getLineNum());
            auto dummy_block = prev_tail;
                // Replace the trailing dummy node from the if block with current block.
                // The dummy block should always be the last block in the mini-CFG for
                // an if statement
                spdlog::debug("deleting dummy block with {} parents: {}\n", dummy_block->parents.size(),*dummy_block);
                // TODO: assert it's a dummy block
                std::string err = "Probably a while conditional stmt (see WhileStatement::get_cfg";
                assert(dummy_block->stmts.size()==0 && err.c_str());
                for(auto parent : dummy_block->parents) {
                    spdlog::debug("Looking at dummy parent wit size {}: {}\n",parent->children.size(),*parent);
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
            spdlog::debug("linking prev_tail = {}\n AND\n new_head={}\n",*prev_tail,*new_head);
            prev_tail->children.push_back(new_head);
            new_head->parents.push_back(prev_tail);
            // Skip this as cond stmt would've added all the parent to curr block links
                // remove the unneeded parent child relationship
                prev_tail->children.pop_back();
                new_head->parents.pop_back();
                assert(prev_tail->children.size()==0);
                assert(new_head->parents.size()==0);
                prev_tail->stmts.push_back(stmt);
                new_blocks.erase(new_blocks.begin());
                spdlog::debug("Removed new_head={} from new_blocks, now new_blocks size = {}\n",*new_head,new_blocks.size());
                if(is_cond_stmt || is_while_stmt) {
                    for(auto child : new_head->children) {
                        prev_tail->children.push_back(child);
                        blocks.erase(std::remove(blocks.begin(),blocks.end(),new_head),blocks.end()); 
                        // Remove the "temp" if block parent which is now obsolete
                        child->parents.erase(std::remove(child->parents.begin(),child->parents.end(),new_head),child->parents.end());
                        child->parents.push_back(prev_tail);
                    }
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
std::string BlockStatement::get_llvm(Bblock &block) { 
	spdlog::debug("inside BlockStatement::{}\n",__func__);
	//std::string llvm_ir="BlockStatement\n";
    std::string llvm_ir = "";
    for(auto stmt : this->statements) {
        llvm_ir += stmt->get_llvm(block);
    }
	return llvm_ir;
} 

std::string BlockStatement::get_arm(Bblock &block) { 
	spdlog::debug("inside BlockStatement::{}\n",__func__);
    std::string arm = "";
    for(auto stmt : this->statements) {
        arm += stmt->get_arm(block);
    }
	return arm;
}
/*
void BlockStatement::resolve_def_uses(Bblock &block) {
    spdlog::debug("inside BlockStatement::{}\n",__func__);
    for(auto stmt : this->statements) {
        stmt->resolve_def_uses(block);
    }
}
*/

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
