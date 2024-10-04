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

//Specialize fmt::formatter for IntType
template <>
struct fmt::formatter<ast::IntType> : fmt::formatter<std::string> {
       auto format(const ast::IntType decl, format_context &ctx) const ->decltype(ctx.out()){
                  return format_to(ctx.out(), "[IntType()]");
                           }
};

#endif // INT_TYPE_HPP

