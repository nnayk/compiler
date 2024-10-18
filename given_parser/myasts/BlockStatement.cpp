#include "BlockStatement.hpp"
#include <cassert>

namespace ast {

// Constructor implementation
BlockStatement::BlockStatement(int lineNum, const std::vector<std::shared_ptr<Statement>>& statements)
    : AbstractStatement(lineNum), statements(statements) {}

void BlockStatement::typecheck(Env &env) {
    for(auto &stmt:statements) {
        stmt->typecheck(env);
    }
}

std::vector<std::shared_ptr<Bblock>> BlockStatement::get_cfg() {
    spdlog::info("inside BlockStatement::{}",__func__);
    // only one block will be created but have to return a vector for 
    // compatability with the get_cfg Statement wide definitin
    auto blocks = std::vector<std::shared_ptr<Bblock>>();
    std::shared_ptr<Bblock> prev_head = nullptr;
    std::vector<std::shared_ptr<Bblock>> prev_blocks;
    std::shared_ptr<Statement> prev_stmt = nullptr;
    for(auto stmt : this->statements) {
        spdlog::debug("BlockStatement:Gonna build cfg for stmt {}",*stmt);
        auto new_blocks = stmt->get_cfg();
        spdlog::debug("BlockStatement:Done building cfg for stmt");
        auto new_head = new_blocks[0];
        if(prev_head) {
            prev_head->children.push_back(new_head);
        }
        //w/o this check the dummy will remain...just test this works as expected
        //for now
        // if the previous block stmt was a conditional, then replace its
        // outbound dummy block with this current block
        /*
        if(dynamic_pointer_cast<ConditionalStatement>(prev_stmt)) {
            // Replace the trailing dummy node from the if block with current block.
            // The dummy block should always be the last block in the mini-CFG for
            // an if statement
            auto dummy_block = prev_blocks[prev_blocks.size()-1];
            for(auto parent : dummy_block) {
                // each parent of the dummy block should only have 1 child
                assert(parent->children.size()==1);
                parent->children[0] = new_head
            }
            //check that dummy goes out of scope now
        }
        */
        prev_stmt = stmt;
        prev_blocks = new_blocks;
        prev_head = new_head;
        blocks.insert(blocks.end(),new_blocks.begin(),new_blocks.end());
    }
    return blocks;
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

