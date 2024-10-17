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
        std::shared_ptr<Bblock> parent;
        std::vector<std::shared_ptr<Bblock>> children;
        Bblock() {}
};

//Specialize fmt::formatter for Bblock
template <>
struct fmt::formatter<Bblock> : fmt::formatter<std::string> {
   auto format(const Bblock &block, format_context &ctx) const ->decltype(ctx.out()) {
   		auto out = fmt::format_to(ctx.out(),"STATEMENTS:");
		for(auto stmt : block.stmts) {
			out = fmt::format_to(out,"{}",*stmt);//->display());
		}
		out = fmt::format_to(out,"NUMBER OF CHILDREN: {}", block.children.size());
		out = fmt::format_to(out,"CHILDREN: ");
		return out;
   }
};
#endif
