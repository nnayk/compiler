#include "AbstractStatement.hpp"

namespace ast {

// Constructor definition
AbstractStatement::AbstractStatement(int lineNum) : lineNum(lineNum) {}

/*
void AbstractStatement::get_cfg(CfgFunc &cfg) {
    spdlog::debug(AbstractStatement::get_cfg); 
}
*/

std::vector<std::shared_ptr<Bblock>> AbstractStatement::get_cfg() {
    // only one block will be created but have to return a vector for 
    // compatability with the get_cfg Statement wide definitin
    auto blocks = std::vector<std::shared_ptr<Bblock>>();
    /*auto block = std::make_shared<Bblock>();
    block->stmts.push_back(std::shared_from_this());
    blocks.push_back(block);
    */return blocks;
}

}  // namespace ast
