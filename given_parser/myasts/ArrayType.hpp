#ifndef ARRAY_TYPE_HPP
#define ARRAY_TYPE_HPP

#include "Type.hpp"

namespace ast {

class ArrayType : public Type {
public:
    // Constructor
    ArrayType() = default;

    // Virtual destructor for proper cleanup
    virtual ~ArrayType() {}
};

}  // namespace ast

#endif  // ARRAY_TYPE_HPP
