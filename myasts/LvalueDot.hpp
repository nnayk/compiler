#ifndef LVALUE_DOT_HPP
#define LVALUE_DOT_HPP

#include "Lvalue.hpp"
#include "AbstractExpression.hpp"
#include <memory>

namespace ast {

class LvalueDot : public Lvalue {
public:
    // Constructor
    LvalueDot(int lineNum, std::shared_ptr<Expression> left, const std::string& id);

    // Getter methods
    int getLineNum() const;
    std::shared_ptr<Expression> getLeft() const;
    std::string getId() const;

private:
    int lineNum;                          // Line number in source code
    std::shared_ptr<Expression> left;     // Left expression
    std::string id;                       // Identifier of the member being accessed
};

} // namespace ast

#endif // LVALUE_DOT_HPP

