#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP
#include "Types.hpp"
#include "Env.hpp"
#include "TypeException.hpp"
#include "Bblock.hpp"
//#include "Register.hpp"
//#include "CfgFunc.hpp"


class Register;
class Bblock;

extern Env structTLE; 
extern Env globalsTLE; 
extern Env funcTLE; 

namespace ast {

// Define an empty interface for Expression
class Expression {
public:
   std::shared_ptr<ast::Type> type = nullptr;
//Don't think this is needed since planning on making resulted protected...
    //    bool set_reg = true; // indicates whether the result of an expression should be stored in a register. For NumExpr and BoolExpr this will be false 
    virtual ~Expression() = default; // Virtual destructor for proper cleanup
    virtual std::shared_ptr<ast::Type> resolveType(Env &env) {return std::make_shared<IntType>();} //TODO URGENT: implement this for each expr
    // This name may be a little confusing since the function was created when
    // I was starting LLVM (m2). Overall this function does operate in an LLVM
    // specific context however. Basically it is responsible for creating all the
    // llvm string output for a given expression. This includes allocing registers.
    virtual std::string get_llvm_init(Bblock &block) = 0;
    // This returns the llvm representation for a given use of an expression.
    // Usually it'll be the llvm for a register but not always (ex. an IntegerExpr
    // will return simply the int in llvm form)
    virtual std::string get_llvm(Bblock &block) = 0;
    // Similar idea to llvm though registers are created well ahead of IR generationin this case. Specifically the virtual registers are allocated during resolve_uses
    // time
    virtual std::string get_ssa_init(Bblock &block) = 0;
    // Similar idea to llvm 
    virtual std::string get_ssa(Bblock &block) = 0;
    // Similar idea to llvm, generate all the boilerplate ARM such that this expression can be referenced by a register or immediate 
    virtual std::string get_arm_init(Bblock &block) = 0;
    // Similar idea to llvm
    virtual std::string get_arm(Bblock &block) = 0;
    // actually idt this is needed
    //virtual std::string get_ssa(CfgFunction &f) = 0;
    virtual std::string display() const = 0;
    virtual std::shared_ptr<Register> getDerefResult() const = 0;
    virtual std::shared_ptr<Register> getResult() const = 0;
    // The purpose of this is for the expression to determine a register for each usage of a variable. This is done by looking up the variable in question and then assigning the result attr to the resolved register
    virtual void resolve_uses(Bblock &block) = 0;
    virtual void replace_reg(std::shared_ptr<Register> target,std::shared_ptr<Register> sub) = 0;
protected:
    std::shared_ptr<Register> result = nullptr; // register where the expression result is stored
    std::shared_ptr<Register> deref_result = nullptr; 
};

}  // namespace ast
//Specialize fmt::formatter for Expression
template <>
struct fmt::formatter<ast::Expression> : fmt::formatter<std::string> {
   auto format(const ast::Expression &expr, format_context &ctx) const ->decltype(ctx.out()) {
       return fmt::format_to(ctx.out(),"{}",expr.display());
   }
};


#endif  // EXPRESSION_HPP
