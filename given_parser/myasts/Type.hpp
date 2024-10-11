#ifndef TYPE_HPP
#define TYPE_HPP
#include <spdlog/spdlog.h>

namespace ast {

class Type {
public:
    // Virtual destructor for proper cleanup of derived classes
    virtual ~Type() = default;
    virtual std::string display() const = 0;
};
}  // namespace ast

//Specialize fmt::formatter for Type
template <>
struct fmt::formatter<ast::Type> : fmt::formatter<std::string> {
       auto format(const ast::Type &t, format_context &ctx) const ->decltype(ctx.out()) {
            return fmt::format_to(ctx.out(),"{}",t.display());
       }
};

#endif
