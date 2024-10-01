#ifndef BLOCKSTATEMENT_HPP
#define BLOCKSTATEMENT_HPP

#include "AbstractStatement.hpp"
#include "Statement.hpp"
#include <vector>
#include <memory>

namespace ast {

class BlockStatement : public AbstractStatement {
private:
    std::vector<std::shared_ptr<Statement>> statements;

public:
    // Constructor
    BlockStatement(int lineNum, const std::vector<std::shared_ptr<Statement>>& statements);

    // Static method to create an empty block
    static std::shared_ptr<BlockStatement> emptyBlock();
};

} // namespace ast

#endif // BLOCKSTATEMENT_HPP
