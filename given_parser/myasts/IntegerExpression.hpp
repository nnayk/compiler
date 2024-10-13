#ifndef INTEGER_EXPRESSION_HPP
#define INTEGER_EXPRESSION_HPP

#include "AbstractExpression.hpp"
#include <string>

namespace ast {

class IntegerExpression : public AbstractExpression {
public:
    // Constructor
    IntegerExpression(int lineNum, const std::string& value);

    // Getter for the value
    std::string getValue() const;
    std::shared_ptr<Type> resolveType(Env &env) override;

private:
    std::string value; // The integer value as a string
};

} // namespace ast

#endif // INTEGER_EXPRESSION_HPP

