#ifndef STATEMENT_HPP
#define STATEMENT_HPP

#include <spdlog/spdlog.h>
#include <string>
#include "Env.hpp"
#include <typeinfo>

namespace ast {

class Statement {
    // This is an empty interface, can add virtual methods if needed in future
public:
    virtual ~Statement() = default; // Virtual destructor for proper cleanup of derived classes
    virtual int getLineNum() const =0;
    virtual std::string display() const = 0;
    virtual void typecheck(Env &env) = 0;
};

} // namespace ast

//Specialize fmt::formatter for Statement
template <>
struct fmt::formatter<ast::Statement> : fmt::formatter<std::string> {
   auto format(const ast::Statement &decl, format_context &ctx) const ->decltype(ctx.out()) {
       return fmt::format_to(ctx.out(),"{}",decl.display());
   }
};

#endif // STATEMENT_HPP

