#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP
#include "Types.hpp"

namespace ast {

// Define an empty interface for Expression
class Expression {
public:
    virtual ~Expression() = default; // Virtual destructor for proper cleanup
    virtual std::shared_ptr<ast::Type> resolveType() {return std::make_shared<IntType>();}
};

}  // namespace ast

#endif  // EXPRESSION_HPP
