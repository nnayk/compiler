#ifndef __PHI__HPP__
#define __PHI__HPP__
#include "Register.hpp"
#include "IdentifierExpression.hpp"
#include <fmt/core.h>
#include <fmt/format.h>

class Phi {
    public:
        std::unordered_map<std::string,std::shared_ptr<Register>> entries;
        std::shared_ptr<Register> assignee = nullptr; // register that's assigned to this phi
        std::shared_ptr<Bblock> block = nullptr; // block that contains this phi
        std::shared_ptr<ast::Type> type = nullptr; // type of the value in register
        std::shared_ptr<ast::IdentifierExpression> id_expr = nullptr; 
        Phi() {};
        void addEntry(std::string label,std::shared_ptr<Register> reg);
        std::string display() const;
        std::string get_ssa();
};

template <>
struct fmt::formatter<Phi> : fmt::formatter<std::string> {
   auto format(const Phi &p, format_context &ctx) const ->decltype(ctx.out()) {
        return format_to(ctx.out(),"{}",p.display());
   }
};
#endif
