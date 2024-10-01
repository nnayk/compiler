#include "LvalueId.hpp"

namespace ast {

// Constructor
LvalueId::LvalueId(int lineNum, const std::string& id)
    : lineNum(lineNum), id(id) {}

// Getter methods
int LvalueId::getLineNum() const {
    return lineNum;
}

std::string LvalueId::getId() const {
    return id;
}

} // namespace ast

