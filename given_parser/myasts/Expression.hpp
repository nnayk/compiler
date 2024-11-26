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
    virtual std::string get_llvm_init(Bblock &block) = 0;
    virtual std::string get_llvm(Bblock &block) = 0;
    virtual std::string get_ssa_init(Bblock &block) = 0;
    virtual std::string get_ssa(Bblock &block) = 0;
    virtual std::string get_arm_init(Bblock &block) = 0;
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
