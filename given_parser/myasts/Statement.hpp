#ifndef STATEMENT_HPP
#define STATEMENT_HPP

#include <string>
#include "Env.hpp"
#include "Function.hpp"
#include "TypeException.hpp"
#include "Bblock.hpp"
//#include "CfgFunc.hpp"
#include <typeinfo>

class Bblock;

namespace ast {
class Function;


class Statement {
    // This is an empty interface, can add virtual methods if needed in future
public:
    bool return_eq = false;
    virtual ~Statement() = default; // Virtual destructor for proper cleanup of derived classes
    virtual int getLineNum() const =0;
    virtual std::string display() const = 0;
    virtual void typecheck(Env &env, Function &f) = 0;
    virtual std::string get_llvm(Bblock &block) = 0;
    virtual std::string get_ssa(Bblock &block) = 0;
    virtual std::string get_arm(Bblock &block) = 0;
    // For all non-block, non-conditional, non-while looop statements, this function will generate a basic block for the statement (technically a cfg w/1 node). For block, conditional, while statements a full cfg will be built. This function is needed at the statement level rather than a more granular statement level b/c it's possible for ASTs for one liner functions to not have any block statement (ex. a return sttmt only)
    virtual std::vector<std::shared_ptr<Bblock>> get_cfg() = 0;
    // The purpose of this function is for the statement to resolve all variable usages for its expression components (see resolve_uses in Expression.hpp for details on that). 
    virtual void resolve_def_uses(Bblock &block) = 0;
    virtual bool guarantees_return(std::shared_ptr<Type> type) = 0;
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

