#ifndef DOT_EXPRESSION_HPP
#define DOT_EXPRESSION_HPP

#include "AbstractExpression.hpp"
#include "Expression.hpp"
#include <string>
#include <memory>

namespace ast {

class DotExpression : public AbstractExpression {
public:
    // Constructor
    DotExpression(int lineNum, std::shared_ptr<Expression> left, const std::string& id);

    // Getter methods for left and id
    std::shared_ptr<Expression> getLeft() const;
    const std::string& getId() const;

private:
    std::shared_ptr<Expression> left_;  // Left expression
    std::string id_;                    // Identifier
};

} // namespace ast

#endif // DOT_EXPRESSION_HPP

