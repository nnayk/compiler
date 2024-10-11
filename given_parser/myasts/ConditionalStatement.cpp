#include "ConditionalStatement.hpp"

namespace ast {

// Constructor implementation
ConditionalStatement::ConditionalStatement(int lineNum, 
                                           std::shared_ptr<Expression> guard, 
                                           std::shared_ptr<Statement> thenBlock, 
                                           std::shared_ptr<Statement> elseBlock)
    : AbstractStatement(lineNum), guard(guard), thenBlock(thenBlock), elseBlock(elseBlock) {}

void ConditionalStatement::typecheck(Env &env) {
}

} // namespace ast

