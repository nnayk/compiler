#include "WhileStatement.hpp"
#include "ConditionalStatement.hpp"

namespace ast {

WhileStatement::WhileStatement(int lineNum, std::shared_ptr<Expression> guard, std::shared_ptr<Statement> body)
    : AbstractStatement(lineNum), guard(guard), body(body) {}

void WhileStatement::typecheck(Env &env) {
}

std::vector<std::shared_ptr<Bblock>> WhileStatement::get_cfg() {
    spdlog::debug("WhileStatement:{}\n",__func__);
	std::vector<std::shared_ptr<Bblock>> blocks;
    // return the blocks with the body and create a final IF block for the cond
    blocks = this->body->get_cfg();
    auto cond_stmt = std::make_shared<ConditionalStatement>(this->lineNum,this->guard,nullptr,nullptr);
    std::shared_ptr<Bblock> tail_block;
    if(blocks.size() > 0) {
        tail_block = blocks[blocks.size()-1];
        tail_block->stmts.push_back(cond_stmt);
    // UPDATE: 10/28 9:35 pm -- this else case is not needed since the loop will be infinite
    // if the body is empty...though it'd still be nice to "support" these kinds of infinite
    // loops :)
    } else {
        std::string err = "URGENT: Update ConditionalStatement get_cfg to deal w/cases where else and/or then are nullptrs -- here both are null";
        assert(true && err.c_str());
        tail_block = cond_stmt->get_cfg()[0]; 
    }
    return blocks;
}

} // namespace ast

