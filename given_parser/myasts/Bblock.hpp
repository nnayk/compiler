#ifndef BBLOCK_HPP
#define BBLOCK_HPP
#include "Statement.hpp"
#include <memory>
#include <fmt/core.h>

namespace ast {
    class BlockStatement;
}
class Bblock {
    public:
        std::vector<std::shared_ptr<ast::Statement>> stmts;
        std::vector<std::shared_ptr<Bblock>> parents;
        std::vector<std::shared_ptr<Bblock>> children;
        int visited; // for display purposes
        Bblock() { visited = 0; }
        std::string get_llvm();
};

//Specialize fmt::formatter for Bblock
template <>
struct fmt::formatter<Bblock> : fmt::formatter<std::string> {
   auto format(const Bblock &block, format_context &ctx) const ->decltype(ctx.out()) {
        auto out = fmt::format_to(ctx.out(),"Head statement: ");
        if(block.stmts.size() > 0)
            out = fmt::format_to(out,"{}",*(block.stmts[0]));
        else
            out = fmt::format_to(out,"Null stmt, dummy block");
        out = fmt::format_to(out,"STATEMENTS:\n");
		for(auto stmt : block.stmts) {
			out = fmt::format_to(out,"{}",*stmt);//->display());
		}
		out = fmt::format_to(out,"\nNUMBER OF CHILDREN: {}\n", block.children.size());
		out = fmt::format_to(out,"CHILDREN:\n");
		for(auto child : block.children) {
            if(child->stmts.size() > 0)
                out = fmt::format_to(out,"HEAD STMT: {}\n",*(child->stmts[0]));
            else
                out = fmt::format_to(out,"DUMMY CHILD");
		}
		out = fmt::format_to(out,"\nNUMBER OF PARENTS: {}\n", block.parents.size());
		out = fmt::format_to(out,"PARENTS:\n");
		for(auto parent : block.parents) {
            if(parent->stmts.size() > 0)
                out = fmt::format_to(out,"HEAD STMT: {}\n",*(parent->stmts[0]));
            else
                out = fmt::format_to(out,"DUMMY parent\n");
		}
		return out;
   }
};
#endif
