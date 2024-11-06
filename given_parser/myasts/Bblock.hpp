#ifndef BBLOCK_HPP
#define BBLOCK_HPP
#include <vector>
#include <memory>
#include <fmt/core.h>
#include <unordered_set>
#include "Statement.hpp"
#include "Label.hpp"
#include "Mapping.hpp"

namespace ast {
    class BlockStatement;
    class Statement;
}

class Mapping;

class Bblock : public std::enable_shared_from_this<Bblock> {
    public: 
        std::vector<std::shared_ptr<ast::Statement>> stmts;
        std::vector<std::shared_ptr<Bblock>> parents;
        std::vector<std::shared_ptr<Bblock>> children;
        std::shared_ptr<Mapping> ssa_map = nullptr;
        std::shared_ptr<Label> label = nullptr;
        std::shared_ptr<Label> jmp_label = nullptr;
        bool emit_llvm = true; // only used by conditionals for then/else blocks for now
        int visited; // for display purposes
        Bblock();
        std::string get_llvm();
        std::string display() const;
        bool is_while_block();
        bool is_cond_block();
        bool is_return_block();
};

//Specialize fmt::formatter for Bblock
template <>
struct fmt::formatter<Bblock> : fmt::formatter<std::string> {
   auto format(const Bblock &block, format_context &ctx) const ->decltype(ctx.out()) {
       return fmt::format_to(ctx.out(),"{}",block.display());
   }
};
#endif
