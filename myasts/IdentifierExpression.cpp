#include "IdentifierExpression.hpp"

namespace ast {

// Constructor
IdentifierExpression::IdentifierExpression(int lineNum, const std::string& id)
    : AbstractExpression(lineNum), id(id) {}

// Getter for the identifier
const std::string& IdentifierExpression::getId() const {
    return id;
}

} // namespace ast

