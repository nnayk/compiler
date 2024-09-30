#ifndef STATEMENT_HPP
#define STATEMENT_HPP

namespace ast {

class Statement {
    // This is an empty interface, can add virtual methods if needed in future
public:
    virtual ~Statement() = default; // Virtual destructor for proper cleanup of derived classes
};

} // namespace ast

#endif // STATEMENT_HPP

