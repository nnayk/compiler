#include "BlockStatement.hpp"

namespace ast {

// Constructor implementation
BlockStatement::BlockStatement(int lineNum, const std::vector<std::shared_ptr<Statement>>& statements)
    : AbstractStatement(lineNum), statements(statements) {}

} // namespace ast

