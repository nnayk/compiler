#include "ConditionalStatement.hpp"
#include "Bblock.hpp"
#include <cassert>

namespace ast {

// Constructor implementation
ConditionalStatement::ConditionalStatement(int lineNum, 
                                           std::shared_ptr<Expression> guard, 
                                           std::shared_ptr<Statement> thenBlock, 
                                           std::shared_ptr<Statement> elseBlock)
    : AbstractStatement(lineNum), guard(guard), thenBlock(thenBlock), elseBlock(elseBlock) {}

void ConditionalStatement::typecheck(Env &env) {
}

std::vector<std::shared_ptr<Bblock>> ConditionalStatement::get_cfg() {
    spdlog::debug("ConditionalStatement:{}",__func__);
	std::vector<std::shared_ptr<Bblock>> blocks;
	auto if_block = std::make_shared<Bblock>(); // The head block
    blocks.push_back(if_block);
	if_block->stmts.push_back(shared_from_this());
    //TODO: 
    // Add left and right children (then and else blocks respectively)
    spdlog::debug("ConditionalStatement:Gonna build cfg for THEN stmt {}",*(this->thenBlock));
    auto then_blocks = this->thenBlock->get_cfg(); 
    //TODO: check that elseBlock is non-null. If it's null then will have to point
    // if_block directly to dummy (guarantee that left/first child is thenBlock and
    // right/second child is elseBlock)
    std::vector<std::shared_ptr<Bblock>> else_blocks;
    //this->elseBlock is guaranteed to be null if there's no else stmt
    if(this->elseBlock) else_blocks = this->elseBlock->get_cfg();
    spdlog::debug("ConditionalStatement: Done building CFGs for then and else");
    auto dummy_block = std::make_shared<Bblock>();
    dummy_block->visited = 21; // Shoddy debugging for now...might just make visited arr a free int and use it as visited or dummy indicator
    // Point the children to a common dummy block. If the children are null point the if block to the dummy
    if(then_blocks.size() > 0) {
        then_blocks[then_blocks.size()-1]->children.push_back(dummy_block);
        dummy_block->parents.push_back(then_blocks[then_blocks.size()-1]);
        if_block->children.push_back(then_blocks[0]);
        blocks.insert(blocks.end(),then_blocks.begin(),then_blocks.end());
        then_blocks[0]->parents.push_back(if_block);
        spdlog::debug("Added then block: {}\n",*then_blocks[0]);
    } else {
        if_block->children.push_back(dummy_block);
        dummy_block->parents.push_back(if_block);
        spdlog::debug("Added then DUMMY block\n");
    }
    if(else_blocks.size() > 0) {
        else_blocks[else_blocks.size()-1]->children.push_back(dummy_block);
        dummy_block->parents.push_back(else_blocks[else_blocks.size()-1]);
        if_block->children.push_back(else_blocks[0]);
        blocks.insert(blocks.end(),else_blocks.begin(),else_blocks.end());
        else_blocks[0]->parents.push_back(if_block);
        spdlog::debug("Added else block: {}\n",*else_blocks[0]);
    } else {
        if_block->children.push_back(dummy_block);
        auto parents = dummy_block->parents;
        auto existing_parent = std::find(parents.begin(),parents.end(),if_block);
        //Add the if block as a parent if not done already. If the then block
        // was empty then the dummy block would've already added if block as a
        // parent in if/else conditional above above
        if(existing_parent == parents.end()) {
            dummy_block->parents.push_back(if_block);
        }
        spdlog::debug("Added else DUMMY block\n");
    }
    //else_blocks[else_blocks.size()-1]->children.push_back(dummy_block);
    // if block has exactly 2 children. TODO: Update this when optimizations are made
    assert(if_block->children.size()==2);
    /*
    for(auto child : if_block->children) {
        blocks.push_back(child);
		spdlog::debug("ADDED CHILD = {}",*child);
    }
    */
    if(std::find(blocks.begin(),blocks.end(),dummy_block) == blocks.end()) {
        spdlog::debug("Pushing dummy block to blocks vector (not a child of if block)");
        blocks.push_back(dummy_block);
    } else {
        spdlog::debug("NOT pushing dummy block to blocks vector again (child of if block)");
    }
    spdlog::debug("Created if block w/{} children\n",if_block->children.size());
    spdlog::debug("{}\n",*blocks[0]);
    spdlog::debug("Conditional statement returning {} blocks\n",blocks.size());
    return blocks;
}

} // namespace ast

