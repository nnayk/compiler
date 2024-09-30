#include "BlockStatement.hpp"

namespace ast {

// Constructor implementation
BlockStatement::BlockStatement(int lineNum, const std::vector<std::shared_ptr<Statement>>& statements)
    : AbstractStatement(lineNum), statements(statements) {}

// Static method to create an empty block
std::shared_ptr<BlockStatement> BlockStatement::emptyBlock() {
    return std::make_shared<BlockStatement>(-1, std::vector<std::shared_ptr<Statement>>());
}

} // namespace ast

