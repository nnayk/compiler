#ifndef NEW_ARRAY_EXPRESSION_HPP
#define NEW_ARRAY_EXPRESSION_HPP

#include "AbstractExpression.hpp"

namespace ast {

class NewArrayExpression : public AbstractExpression {
public:
    // Constructor
    NewArrayExpression(int lineNum, const std::string& size);

    // Getter method for size
    const std::string& getSize() const;

private:
    std::string size; // Size of the new array
};

} // namespace ast

#endif // NEW_ARRAY_EXPRESSION_HPP

