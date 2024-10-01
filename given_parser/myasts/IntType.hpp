#ifndef INT_TYPE_HPP
#define INT_TYPE_HPP

#include "Type.hpp"

namespace ast {

class IntType : public Type {
public:
    // Constructor
    IntType() {}

    // Destructor
    virtual ~IntType() = default; // Default virtual destructor
};

} // namespace ast

#endif // INT_TYPE_HPP

