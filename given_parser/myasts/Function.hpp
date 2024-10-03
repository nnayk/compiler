#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <string>
#include <list>
#include <memory>
#include "Declaration.hpp"
#include "Statement.hpp"

namespace ast {

class Function {
public:
    int lineNum;  // Line number of the function definition
    std::string name;  // Name of the function
    std::list<std::shared_ptr<Declaration>> params;  // Function parameters
    std::shared_ptr<Type> retType;  // Return type
    std::list<std::shared_ptr<Declaration>> locals;  // Local declarations
    std::shared_ptr<Statement> body;  // Function body
    // Constructor
    Function(int lineNum, const std::string& name,
             const std::list<std::shared_ptr<Declaration>>& params,
             std::shared_ptr<Type> retType,
             const std::list<std::shared_ptr<Declaration>>& locals,
             std::shared_ptr<Statement> body);
};

} // namespace ast

 //Specialize fmt::formatter for Function
 template <>
 struct fmt::formatter<ast::Function> : fmt::formatter<std::string> {
    auto format(const ast::Function decl, format_context &ctx) const ->decltype(ctx.out()
       ) {
              auto out = format_to(ctx.out(), "[Function(lineNum = {},name={},retType={})", decl.lineNum,decl.name,*decl.retType);
              out = format_to(out, ", params = [");
              bool first=true;
              for(auto param:decl.params) {
                 if(!first) {
                     out=format_to(out,", ");
                 }
                 out=format_to(out,"{}",*param);
                 first=false;
              }
              out=format_to(out,"]]");
              return out;
                       }
};

#endif // FUNCTION_HPP

