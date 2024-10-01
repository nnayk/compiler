#include "NewExpression.hpp"

namespace ast {

// Constructor
NewExpression::NewExpression(int lineNum, const std::string& id)
    : AbstractExpression(lineNum), id(id) {}

// Getter method for id
const std::string& NewExpression::getId() const {
    return id;
}

} // namespace ast

