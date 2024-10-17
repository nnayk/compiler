#include "AbstractStatement.hpp"

namespace ast {

// Constructor definition
AbstractStatement::AbstractStatement(int lineNum) : lineNum(lineNum) {}

/*
void AbstractStatement::add_to_cfg(CfgFunc &cfg) {
    spdlog::debug(AbstractStatement::add_to_cfg); 
}
*/

}  // namespace ast
