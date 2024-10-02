#ifndef DECLARATION_HPP
#define DECLARATION_HPP

#include <string>
#include <memory>
#include "Type.hpp"  // Assuming you have a Type class defined
#include <spdlog/spdlog.h>

namespace ast {

class Declaration {
public:
    // Constructor
    Declaration(int lineNum, std::shared_ptr<Type> type, const std::string& name);

    // Getters
    int getLineNum() const;
    std::shared_ptr<Type> getType() const;
    const std::string& getName() const;

private:
    int lineNum_;
    std::shared_ptr<Type> type_;
    std::string name_;
};

} // namespace ast
//Specialize fmt::formatter for Declaration
template <>
struct fmt::formatter<ast::Declaration> : fmt::formatter<std::string> {
   auto format(const ast::Declaration decl, format_context &ctx) const ->decltype(ctx.out()
   ) {
       return format_to(ctx.out(), "[Declaration(lineNum = {},var={},type={})]", decl.getLineNum(),decl.getName(),*decl.getType());
         }
};
#endif // DECLARATION_HPP

