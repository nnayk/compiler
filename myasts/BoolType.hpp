#ifndef BOOLTYPE_HPP
#define BOOLTYPE_HPP

#include "Type.hpp"

namespace ast {

class BoolType : public Type {
public:
    // Constructor
    BoolType() = default;

    // Destructor
    virtual ~BoolType() = default;
};

} // namespace ast

#endif // BOOLTYPE_HPP

