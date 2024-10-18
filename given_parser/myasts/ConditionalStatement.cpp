#include "ConditionalStatement.hpp"
#include "Bblock.hpp"

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
	if_block->stmts.push_back(shared_from_this());
    //TODO: 
    // Add left and right children (then and else blocks respectively)
    spdlog::debug("ConditionalStatement:Gonna build cfg for THEN stmt {}",*(this->thenBlock));
    auto then_blocks = this->thenBlock->get_cfg(); 
    //TODO: check that elseBlock is non-null. If it's null then will have to point
    // if_block directly to dummy (guarantee that left/first child is thenBlock and
    // right/second child is elseBlock)
    //auto else_blocks = this->elseBlock->get_cfg();
    spdlog::debug("ConditionalStatement: Done building CFGs for then and else");
    auto dummy_block = std::make_shared<Bblock>();
    dummy_block->visited = 21; // Shoddy debugging for now...might just make visited arr a free int and use it as visited or dummy indicator
    // Point the children to a common dummy block
    then_blocks[then_blocks.size()-1]->children.push_back(dummy_block);
    //else_blocks[else_blocks.size()-1]->children.push_back(dummy_block);
    blocks.push_back(if_block);
    return blocks;
}

} // namespace ast

