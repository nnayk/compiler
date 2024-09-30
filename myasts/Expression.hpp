#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

namespace ast {

// Define an empty interface for Expression
class Expression {
public:
    virtual ~Expression() = default; // Virtual destructor for proper cleanup
};

}  // namespace ast

#endif  // EXPRESSION_HPP
