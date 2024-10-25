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
    std::shared_ptr<Type> resolveType(Env &env) override;
    std::string display() const override {
        return fmt::format("IdentifierExpression(lineNum={},id={})\n",lineNum,this->getId());
    }

private:
    std::string id;  // Identifier string
};

} // namespace ast

#endif // IDENTIFIER_EXPRESSION_HPP

