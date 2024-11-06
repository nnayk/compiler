#ifndef BLOCKSTATEMENT_HPP
#define BLOCKSTATEMENT_HPP

#include "AbstractStatement.hpp"
#include "Statement.hpp"
#include "Env.hpp"
#include <vector>
#include <memory>
#include <spdlog/spdlog.h>

namespace ast {

class BlockStatement : public AbstractStatement {
public:
    std::vector<std::shared_ptr<Statement>> statements;
    std::unordered_set<std::shared_ptr<Bblock>> return_bblocks;
    // Constructor
    BlockStatement(int lineNum, const std::vector<std::shared_ptr<Statement>>& statements);
    virtual void typecheck(Env &env, Function &f) override;

	// Static method to create an empty block
	static std::shared_ptr<BlockStatement> emptyBlock();
	std::string display() const override {
        spdlog::debug("inside BlockStatement:{}\n",__func__);
		std::string result = "START OF BLOCK STATEMENTS\n";
		result += fmt::format("BlockStatement(lineNum={}, statements=[", lineNum);
		
		for (const auto& stmt : statements) {
			result += stmt->display() + ", ";
		}
		
		result += "])\nEND OF BLOCKSTATEMENT";
		return result;
	}
    virtual std::vector<std::shared_ptr<Bblock>> get_cfg() override;
    virtual std::string get_llvm(Bblock &block) override;
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
