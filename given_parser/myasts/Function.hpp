#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <string>
#include <vector>
#include <memory>
#include "Declaration.hpp"
#include "Statement.hpp"
#include "Env.hpp"

namespace ast {
class Statement;
class Function {
public:
    int lineNum;  // Line number of the function definition
    std::string name;  // Name of the function
    std::vector<Declaration> params;  // Function parameters
    std::shared_ptr<Type> retType;  // Return type
    std::vector<Declaration> locals;  // Local declarations
    std::shared_ptr<Statement> body;  // Function body
    const std::string& getName() const;
    std::shared_ptr<Env> env;
    // Constructor
    Function(int lineNum, const std::string& name,
             const std::vector<Declaration>& params,
             std::shared_ptr<Type> retType,
             const std::vector<Declaration>& locals,
             std::shared_ptr<Statement> body);
    void typecheck(Env env);
};

} // namespace ast

 //Specialize fmt::formatter for Function
 template <>
 struct fmt::formatter<ast::Function> : fmt::formatter<std::string> {
    auto format(const ast::Function decl, format_context &ctx) const ->decltype(ctx.out()
       ) {
              spdlog::debug("Formatter for Function");
              auto out = format_to(ctx.out(), "[Function(lineNum = {},name={},retType={})", decl.lineNum,decl.name,*decl.retType);// TODO: bring this back -- add a get_body function or smth in Function.cpp. rn get an err b/c statement if fwd declared in this file ,*decl.body);
              out = format_to(out, ", params = [");
              bool first=true;
              spdlog::debug("generating param output\n");
              for(auto param:decl.params) {
                 if(!first) {
                     out=format_to(out,", ");
                 }
                 out=format_to(out,"{}",param);
                 first=false;
              }
              out=format_to(out,"]");
              out = format_to(out, ", locals = [");
              first=true;
              for(auto local:decl.locals) {
                 if(!first) {
                     out=format_to(out,", ");
                 }
                 out=format_to(out,"{}",local);
                 first=false;
              }
              out=format_to(out,"]]");
              return out;
                       }
};

#endif // FUNCTION_HPP

