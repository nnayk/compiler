#ifndef IDENTIFIER_EXPRESSION_HPP
#define IDENTIFIER_EXPRESSION_HPP

#include <string>
#include "AbstractExpression.hpp"

namespace ast {

class IdentifierExpression : public AbstractExpression {
public:
    // Constructor
    IdentifierExpression(int lineNum, const std::string& id);

    // Getter for the identifier
    const std::string& getId() const;

private:
    std::string id;  // Identifier string
};

} // namespace ast

#endif // IDENTIFIER_EXPRESSION_HPP

