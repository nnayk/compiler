#include "LvalueIndex.hpp"

namespace ast {

// Constructor
LvalueIndex::LvalueIndex(int lineNum, std::shared_ptr<Lvalue> left, std::shared_ptr<Expression> index)
    : lineNum(lineNum), left(left), index(index) {}
} // namespace ast

