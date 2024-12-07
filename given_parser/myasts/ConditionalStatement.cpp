#include "ConditionalStatement.hpp"
#include "BlockStatement.hpp"
#include "Bblock.hpp"
#include <cassert>

extern std::string TAB;

namespace ast {

// Constructor implementation
ConditionalStatement::ConditionalStatement(int lineNum, 
                                           std::shared_ptr<Expression> guard, 
                                           std::shared_ptr<Statement> thenBlock, 
                                           std::shared_ptr<Statement> elseBlock)
    : AbstractStatement(lineNum), guard(guard), thenBlock(thenBlock), elseBlock(elseBlock) {}

void ConditionalStatement::typecheck(Env &env, Function &f) {
    auto guard_type = this->guard->resolveType(env);
    if(!dynamic_pointer_cast<BoolType>(guard_type)) {
        throw TypeException(fmt::format("Expected boolean guard, got type {} instead",*guard_type));
    }
    if(this->thenBlock) this->thenBlock->typecheck(env,f);
    if(this->elseBlock) this->elseBlock->typecheck(env,f);
}

std::vector<std::shared_ptr<Bblock>> ConditionalStatement::get_cfg() {
    spdlog::debug("ConditionalStatement:{}",__func__);
	std::vector<std::shared_ptr<Bblock>> blocks;
	auto if_block = std::make_shared<Bblock>(); // The head block
    assert(if_block->visited==0);
    blocks.push_back(if_block);
	if_block->stmts.push_back(shared_from_this());
    //TODO: 
    // Add left and right children (then and else blocks respectively)
    std::vector<std::shared_ptr<Bblock>> then_blocks;
    if(this->thenBlock) {
        spdlog::debug("ConditionalStatement:Gonna build cfg for THEN stmt {}",*(this->thenBlock));
        then_blocks = this->thenBlock->get_cfg();
    } else {
        spdlog::debug("then block is null, not building a cfg\n");
    }
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
        // if the then block was empty and now the else block was empty then there's already a parent-child relatonship between if block and dummy block. so don't do anything now. UPDATE: this case will be impossible once I just skip over such useless if statements...
        auto existing_relationship = std::find(if_block->children.begin(),if_block->children.end(),dummy_block);
        if(existing_relationship == if_block->children.end()) {
            if_block->children.push_back(dummy_block);
            dummy_block->parents.push_back(if_block);
            spdlog::debug("Added else DUMMY block\n");
        }
    }
    //else_blocks[else_blocks.size()-1]->children.push_back(dummy_block);
    // if block has exactly 2 children (or exactly 1 if both then/else are empty OR if it's a while conditional makeshift). TODO: Update this when optimizations are made
    assert(if_block->children.size()==2 || if_block->children.size()==1);
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
    //spdlog::debug("{}\n",*blocks[0]);
    spdlog::debug("Conditional statement returning {} blocks\n",blocks.size());
    assert(if_block->visited==0);
    return blocks;
}

std::string ConditionalStatement::get_llvm(Bblock &block) {
    spdlog::debug("inside ConditionalStatement::{}\n",__func__);
    spdlog::debug("line={}\n",this->getLineNum());
	assert(block.children.size()==2);
	auto thenLabel = block.children[0]->label->getLabel();
	auto elseLabel = block.children[1]->label->getLabel();
    std::string llvm = this->guard->get_llvm_init(block);
    llvm += TAB+fmt::format("br i1 {}, label %{}, label %{}\n",this->guard->get_llvm(block),thenLabel,elseLabel);
    spdlog::debug("llvm={}\n",llvm);
    return llvm;
}

std::string ConditionalStatement::get_ssa(Bblock &block) {
    spdlog::debug("inside ConditionalStatement::{}\n",__func__);
    spdlog::debug("line={}\n",this->getLineNum());
	assert(block.children.size()==2);
	auto thenLabel = block.children[0]->label->getLabel();
	auto elseLabel = block.children[1]->label->getLabel();
    std::string ssa = this->guard->get_ssa_init(block);
    ssa += TAB+fmt::format("br i1 {}, label %{}, label %{}\n",this->guard->get_ssa(block),thenLabel,elseLabel);
    spdlog::debug("ssa={}\n",ssa);
    return ssa;
}

void ConditionalStatement::resolve_def_uses(Bblock &block) {
    spdlog::debug("inside ConditionalStatement::{}\n",__func__);
    this->guard->resolve_uses(block);
    //this->thenBlock->resolve_def_uses(block);
    //this->elseBlock->resolve_def_uses(block);
}

std::string ConditionalStatement::get_arm(Bblock &block) {
    spdlog::debug("inside ConditionalStatement::{}\n",__func__);
    std::string arm = "";
    // TODO: support chained conditions, rn only assuming 1 condition
    arm += guard->get_arm_init(block);
    // Bool Type
    // Binary Expression -- need to determine the appropriate operator to use (i.e. bgt,ble,be,etc.)
    return arm;
}

} // namespace ast

