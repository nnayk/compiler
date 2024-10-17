#ifndef STATEMENT_HPP
#define STATEMENT_HPP

#include <spdlog/spdlog.h>
#include <string>
#include "Env.hpp"
//#include "Bblock.hpp"
//#include "CfgFunc.hpp"
#include <typeinfo>

class Bblock;
namespace ast {


class Statement {
    // This is an empty interface, can add virtual methods if needed in future
public:
    virtual ~Statement() = default; // Virtual destructor for proper cleanup of derived classes
    virtual int getLineNum() const =0;
    virtual std::string display() const = 0;
    virtual void typecheck(Env &env) = 0;
    // For all non-block, non-conditional, non-while looop statements, this function will generate a basic block for the statement (technically a cfg w/1 node). For block, conditional, while statements a full cfg will be built. This function is needed at the statement level rather than a more granular statement level b/c it's possible for ASTs for one liner functions to not have any block statement (ex. a return sttmt only)
    virtual std::vector<std::shared_ptr<Bblock>> get_cfg() = 0;
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

