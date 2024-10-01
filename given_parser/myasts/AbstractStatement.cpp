#include "AbstractStatement.hpp"

namespace ast {

// Constructor definition
AbstractStatement::AbstractStatement(int lineNum) : lineNum(lineNum) {}

// Getter for lineNum
int AbstractStatement::getLineNum() const {
    return lineNum;
}

}  // namespace ast
