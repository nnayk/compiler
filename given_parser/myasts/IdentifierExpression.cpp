#include "IdentifierExpression.hpp"

namespace ast {

// Constructor
IdentifierExpression::IdentifierExpression(int lineNum, const std::string& id)
    : AbstractExpression(lineNum), id(id) {}

// Getter for the identifier
const std::string& IdentifierExpression::getId() const {
    return id;
}

std::shared_ptr<Type> IdentifierExpression::resolveType(Env &env) {
    auto id = this->getId();
    auto entry = env.lookup(id);
    if(entry) {
        return entry->type; 
    } else {
        throw TypeException(fmt::format("Unknown identifier {}",id));
    }
}
} // namespace ast

