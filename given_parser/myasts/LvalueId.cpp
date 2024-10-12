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

/*
Resolve the Lvalue to a base type. If not possible raise an exception.
*/
 std::shared_ptr<Type> LvalueId::resolveType() const {
    return std::make_shared<NullType>();
}

} // namespace ast

