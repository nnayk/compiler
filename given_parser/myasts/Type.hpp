#ifndef TYPE_HPP
#define TYPE_HPP

namespace ast {

class Type {
public:
    // Virtual destructor for proper cleanup of derived classes
    virtual ~Type() = default;
};
    
}  // namespace ast
#endif
