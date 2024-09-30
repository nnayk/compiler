#ifndef LVALUE_INDEX_HPP
#define LVALUE_INDEX_HPP

#include "Lvalue.hpp"
#include "Expression.hpp"

namespace ast {

class LvalueIndex : public Lvalue {
public:
    // Constructor
    LvalueIndex(int lineNum, Expression* left, Expression* index);

    // Getter methods
    int getLineNum() const;
    Expression* getLeft() const;
    Expression* getIndex() const;

private:
    int lineNum;           // Line number in source code
    Expression* left;      // Expression on the left side
    Expression* index;     // Expression representing the index
};

} // namespace ast

#endif // LVALUE_INDEX_HPP

