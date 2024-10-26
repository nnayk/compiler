#ifndef TYPEDECLARATION_HPP
#define TYPEDECLARATION_HPP

#include <string>
#include <vector>
#include "Declaration.hpp"

namespace ast {

class TypeDeclaration {
public:
    int size;
    int lineNum;
    std::string name;
    std::vector<Declaration> fields;
    //std::string llvm_str;
    TypeDeclaration(int lineNum, const std::string& name, const std::vector<Declaration>& fields);
    std::string get_llvm();
    std::string get_llvm_init();
};

} // namespace ast
//Specialize fmt::formatter for Declaration
template <>
struct fmt::formatter<ast::TypeDeclaration> : fmt::formatter<std::string> {
   auto format(const ast::TypeDeclaration decl, format_context &ctx) const ->decltype(ctx.out()
      ) {
             auto out = format_to(ctx.out(), "[TypeDeclaration(lineNum = {},var={})", decl.lineNum,decl.name);
             out = format_to(out, ", fields = [");
             bool first=true;
             for(auto field:decl.fields) {
                if(!first) {
                    out=format_to(out,", ");
                }
                out=format_to(out,"{}",field);
                first=false;
             }
             out=format_to(out,"]]");
             return out;
                      }
                      };
#endif // TYPEDECLARATION_HPP

