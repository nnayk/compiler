#include "WhileStatement.hpp"
#include "ConditionalStatement.hpp"
#include "BlockStatement.hpp"

namespace ast {

WhileStatement::WhileStatement(int lineNum, std::shared_ptr<Expression> guard, std::shared_ptr<Statement> body)
    : AbstractStatement(lineNum), guard(guard), body(body) {}

void WhileStatement::typecheck(Env &env, Function &f) {
    spdlog::debug("inside WhileStatement::{}\n",__func__);
    spdlog::debug("line = {}\n",this->getLineNum());
    auto guard_type = this->guard->resolveType(env);
    if(!dynamic_pointer_cast<BoolType>(guard_type)) {
        throw TypeException(fmt::format("Expected boolean guard, got type {} instead",*guard_type));
    }
    this->body->typecheck(env,f);
}

std::vector<std::shared_ptr<Bblock>> WhileStatement::get_cfg() {
    spdlog::debug("WhileStatement:{}\n",__func__);
	std::vector<std::shared_ptr<Bblock>> blocks;
    // TODO: check if the body is empty... it'd be nice to "support" infinite loops :)
    assert(this->body); 
    //blocks = this->body->get_cfg();
    //auto cond_stmt = std::make_shared<ConditionalStatement>(this->lineNum,this->guard,shared_from_this(),nullptr);
    auto cond_stmt = std::make_shared<ConditionalStatement>(this->lineNum,this->guard,this->body,nullptr);
    assert(!cond_stmt->elseBlock);
    blocks = cond_stmt->get_cfg();
    //assert(blocks.size()==3);
    auto if_block = blocks[0];
    assert(if_block->children.size()==2);
    auto dummy_block = if_block->children[1];
    assert(dummy_block->stmts.size()==0);
    assert(dummy_block->parents.size()==2);
    std::shared_ptr<Bblock> thenBlock = if_block->children[0];
    auto final_body_block = dummy_block->parents[0];
    assert(final_body_block != if_block);
    // It's possible that the final body block is itsel a dummy (i.e. if within
    // a while. In this case reset the visited from dummy default (currenlty 21
    // to 0)
    if(final_body_block->stmts.size()==0) final_body_block->visited = 0;
    // Add conditional stmt to last block in body block
    //auto cond_stmt_copy = std::make_shared<ConditionalStatement>(this->lineNum,this->guard,this->body,nullptr);
    final_body_block->stmts.push_back(cond_stmt);
    // Add self loop (as 1st child)
    final_body_block->children[0] = thenBlock;
    thenBlock->parents.push_back(final_body_block);
    thenBlock->loopback_parents.push_back(final_body_block);
    final_body_block->children.push_back(dummy_block);
    return blocks;
}

std::string WhileStatement::get_llvm(Bblock &block) {
    spdlog::debug("inside WhileStatement::{}\n",__func__);
    std::string llvm = "";
    assert(!this->label); // a parent block should've set this in Bblock::get_llvm() for CondStatement case
    assert(!this->afterLabel); 
    auto body_block = dynamic_pointer_cast<BlockStatement>(this->body);
    for(auto stmt: body_block->statements) {
        llvm += stmt->get_llvm(block);
    }
    return llvm;
}

} // namespace ast

