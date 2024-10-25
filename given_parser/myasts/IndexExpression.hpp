#ifndef INDEX_EXPRESSION_HPP
#define INDEX_EXPRESSION_HPP

#include "AbstractExpression.hpp"
#include <memory>

namespace ast {

class IndexExpression : public AbstractExpression {
public:
    // Constructor
    IndexExpression(int lineNum, std::shared_ptr<Expression> left, std::shared_ptr<Expression> index);

    // Getters for left and index expressions
    std::shared_ptr<Expression> getLeft() const;
    std::shared_ptr<Expression> getIndex() const;
    std::string display() const override {
        // Not supporting IndexExpr for now so idc about the display
        return fmt::format("IndexExpression(lineNum={})\n",lineNum);
    }

private:
    std::shared_ptr<Expression> left;  // Left expression
    std::shared_ptr<Expression> index; // Index expression
};

} // namespace ast

#endif // INDEX_EXPRESSION_HPP

