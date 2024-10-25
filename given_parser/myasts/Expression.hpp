#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP
#include "Types.hpp"
#include "Env.hpp"
#include "TypeException.hpp"
//#include "Register.hpp"

class Register;

extern Env structTLE; 
extern Env globalsTLE; 
extern Env funcTLE; 

namespace ast {

// Define an empty interface for Expression
class Expression {
public:
//Don't think this is needed since planning on making resulted protected...
    //    bool set_reg = true; // indicates whether the result of an expression should be stored in a register. For NumExpr and BoolExpr this will be false 
    virtual ~Expression() = default; // Virtual destructor for proper cleanup
    virtual std::shared_ptr<ast::Type> resolveType(Env &env) {return std::make_shared<IntType>();}
    virtual std::string get_llvm_init() = 0;
    virtual std::string get_llvm() = 0;
    virtual std::string display() const = 0;
protected:
    std::shared_ptr<Register> result = nullptr; // register where the expression result is stored
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
