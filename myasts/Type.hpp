#ifndef TYPE_HPP
#define TYPE_HPP

namespace ast {

class Type {
public:
    // Virtual destructor for proper cleanup of derived classes
    virtual ~Type() = default;

    // Pure virtual function to make this an abstract class
    virtual void someTypeMethod() const = 0;  // Replace
};
    
}  // namespace ast
#endif
