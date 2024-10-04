#ifndef LVALUE_INDEX_HPP
#define LVALUE_INDEX_HPP

#include "Lvalue.hpp"
#include "Expression.hpp"

namespace ast {

class LvalueIndex : public Lvalue {
public:
    int lineNum;           // Line number in source code
    std::shared_ptr<Lvalue> left;      // Lvalue on the left side
    std::shared_ptr<Expression> index;     // Lvalue representing the index
    // Constructor
    LvalueIndex(int lineNum, std::shared_ptr<Lvalue> left, std::shared_ptr<Expression> index);
};

} // namespace ast

#endif // LVALUE_INDEX_HPP

