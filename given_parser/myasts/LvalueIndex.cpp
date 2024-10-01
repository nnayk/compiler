#include "LvalueIndex.hpp"

namespace ast {

// Constructor
LvalueIndex::LvalueIndex(int lineNum, Expression* left, Expression* index)
    : lineNum(lineNum), left(left), index(index) {}

// Getter methods
int LvalueIndex::getLineNum() const {
    return lineNum;
}

Expression* LvalueIndex::getLeft() const {
    return left;
}

Expression* LvalueIndex::getIndex() const {
    return index;
}

} // namespace ast

