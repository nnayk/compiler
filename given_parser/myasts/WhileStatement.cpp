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
    auto tail_block = blocks[blocks.size()-1];
    tail_block->stmts.push_back(cond_stmt);
    return blocks;
}

} // namespace ast

