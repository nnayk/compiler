#ifndef BLOCKSTATEMENT_HPP
#define BLOCKSTATEMENT_HPP

#include "AbstractStatement.hpp"
#include "Statement.hpp"
#include <vector>
#include <memory>
#include <spdlog/spdlog.h>

namespace ast {

class BlockStatement : public AbstractStatement {
public:
    int lineNum;
    std::vector<std::shared_ptr<Statement>> statements;
    // Constructor
    BlockStatement(int lineNum, const std::vector<std::shared_ptr<Statement>>& statements);

    // Static method to create an empty block
    static std::shared_ptr<BlockStatement> emptyBlock();
};

} // namespace ast

 //Specialize fmt::formatter for Function
 template <>
 struct fmt::formatter<ast::BlockStatement> : fmt::formatter<std::string> {
    auto format(const ast::BlockStatement decl, format_context &ctx) const ->decltype(ctx.out()
       ) {
              return format_to(ctx.out(), "[BlockStatement(lineNum = {},# of statements = {})", decl.lineNum,decl.statements.size());
              // TODO: print the child statement instances (similar to Type() issue)
              /*
              auto out = format_to(ctx.out(), "[BlockStatement(lineNum = {},statements = [)", decl.lineNum);
              bool first=true;
              for(auto statement:decl.statements) {
                 if(!first) {
                     out=format_to(out,", ");
                 }
                 out=format_to(out,"{}",statement);
                 first=false;
              }
              out=format_to(out,"]");
              return out;
              */
                       }
};
#endif // BLOCKSTATEMENT_HPP
