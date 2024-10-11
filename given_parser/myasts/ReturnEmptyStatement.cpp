#include "ReturnEmptyStatement.hpp"

namespace ast {

// Constructor that calls the base class constructor
ReturnEmptyStatement::ReturnEmptyStatement(int lineNum)
    : AbstractStatement(lineNum) {}

void ReturnEmptyStatement::typecheck(Env &env) {
}

} // namespace ast

