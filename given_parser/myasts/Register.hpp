#ifndef REGISTER_HPP
#define REGISTER_HPP
#include <string>
#include <memory>
#include "Expression.hpp"
#include "Type.hpp"

namespace ast {
    class Expression;
}
class Register;
class Phi;
// global map of all registers
class Register : public std::enable_shared_from_this<Register> {
    public:
        static std::string LOCAL_PREFIX;
        static std::string GLOBAL_PREFIX;
        std::shared_ptr<ast::Type> content_type; // type of the value in register
        bool pseudo = false;
        static std::shared_ptr<Register> create(const std::string &id = std::to_string(reg),const bool &is_global=false,const bool &is_pseudo=false);
        void set_global(); // Discovered that an ID was global when resolving type and now must adjust the register prefix
        std::string get_id();
        std::string get_prefix();
        void set_global_prefix();
        std::string get_llvm();
        std::string get_arm();
        void replace_reg(std::shared_ptr<Register> sub);
        void add_exp(std::shared_ptr<ast::Expression> exp); 
        void add_phi(std::shared_ptr<Phi> phi); 
        //std::string use_llvm(std::shared_ptr<ast::Expression>);
    private:
        Register(const std::string &id = std::to_string(reg),const bool &is_global=false,const bool &is_pseudo=false);
        std::vector<std::shared_ptr<ast::Expression>> exp_references; // for quickly updating a register's usage for SSA trivial phi deletion
        std::vector<std::shared_ptr<Phi>> phi_refs; // for quickly updating a register's usage for SSA trivial phi deletion
        std::string prefix;
        std::string id;
        static int reg;
};

//Specialize fmt::formatter for Type
template <>
struct fmt::formatter<Register> : fmt::formatter<std::string> {
       auto format(Register &r, format_context &ctx) const ->decltype(ctx.out()) {
           std::string prefix = "";
            if(!r.pseudo) prefix = r.get_prefix();
            return fmt::format_to(ctx.out(),"Register(id = {}{}, pseudo = {})",prefix,r.get_id(), r.pseudo);
       }
};


#endif
