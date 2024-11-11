#ifndef BBLOCK_HPP
#define BBLOCK_HPP
#include <vector>
#include <memory>
#include <fmt/core.h>
#include <unordered_set>
#include "Statement.hpp"
#include "Label.hpp"
#include "Mapping.hpp"
#include "Register.hpp"

namespace ast {
    class BlockStatement;
    class Statement;
}

class Mapping;

class Bblock : public std::enable_shared_from_this<Bblock> {
    public: 
        std::vector<std::shared_ptr<ast::Statement>> stmts;
        std::vector<std::shared_ptr<Bblock>> parents;
        std::vector<std::shared_ptr<Bblock>> loopback_parents;
        std::vector<std::shared_ptr<Bblock>> children;
        std::shared_ptr<Mapping> ssa_map = nullptr;
        std::shared_ptr<Label> label = nullptr;
        bool emit_llvm = true; // only used by conditionals for then/else blocks for now
        bool sealed = true; // basically if a block has a potential future pred. (which can only be the case with while body blocks) then it will be unsealed until the future pred. is sealed.
        int visited; // for CFG traversal purposes
        bool final_return_block = false;
        Bblock();
        std::string get_llvm();
        std::string display() const;
        bool is_while_block();
        bool is_cond_block();
        bool is_return_block();
        std::shared_ptr<Register> lookup(std::string id);
        bool is_loopback_parent(std::shared_ptr<Bblock> target);
        void add_phis(std::vector<ast::Declaration> locals,std::vector<ast::Declaration> params); 
        void resolve_def_uses(); // traverses each stmt, updating each expression with its result register and updating mapping for each assignment encountered
};

//Specialize fmt::formatter for Bblock
template <>
struct fmt::formatter<Bblock> : fmt::formatter<std::string> {
   auto format(const Bblock &block, format_context &ctx) const ->decltype(ctx.out()) {
       return fmt::format_to(ctx.out(),"{}",block.display());
   }
};
#endif
