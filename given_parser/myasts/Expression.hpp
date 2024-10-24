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
    std::shared_ptr<Register> result = nullptr; // register where the expression result is stored
    virtual ~Expression() = default; // Virtual destructor for proper cleanup
    virtual std::shared_ptr<ast::Type> resolveType(Env &env) {return std::make_shared<IntType>();}
    virtual std::string get_llvm() = 0;
};

}  // namespace ast

#endif  // EXPRESSION_HPP
