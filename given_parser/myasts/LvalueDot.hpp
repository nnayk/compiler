#ifndef LVALUE_DOT_HPP
#define LVALUE_DOT_HPP

#include "Lvalue.hpp"
#include "Expression.hpp"
#include <memory>

namespace ast {

class LvalueDot : public Lvalue {
public:
    int lineNum;                          // Line number in source code
    std::shared_ptr<Lvalue> left;     // Left expression
    std::string id;                       // Identifier of the member being accessed
    // Constructor
    LvalueDot(int lineNum, std::shared_ptr<Lvalue> left, const std::string& id);

    // Getter methods
    int getLineNum() const;
    std::shared_ptr<Lvalue> getLeft() const;
    std::shared_ptr<Type> resolveType() const override;
    std::string getId() const override;
};

} // namespace ast

#endif // LVALUE_DOT_HPP

