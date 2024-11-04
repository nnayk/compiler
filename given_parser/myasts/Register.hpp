#ifndef REGISTER_HPP
#define REGISTER_HPP
#include <string>
#include <memory>
#include "Expression.hpp"
#include "Type.hpp"

class Register;
// global map of all registers
class Register : public std::enable_shared_from_this<Register> {
    public:
        static std::string LOCAL_PREFIX;
        static std::string GLOBAL_PREFIX;
        std::shared_ptr<ast::Type> content_type; // type of the value in register
        bool pseudo = false;
        Register(const std::string &id = std::to_string(reg),const bool &is_global=false,const bool &is_pseudo=false);
        static std::shared_ptr<Register> create(const std::string &id = std::to_string(reg),const bool &is_global=false,const bool &is_pseudo=false);
        void set_global(); // Discovered that an ID was global when resolving type and now must adjust the register prefix
        std::string get_id();
        std::string get_prefix();
        void set_global_prefix();
        std::string get_llvm();
        //std::string use_llvm(std::shared_ptr<ast::Expression>);
    private:
        std::vector<std::shared_ptr<ast::Expression>> references; // for quickly updating a register's usage for SSA trivial phi deletion
        std::string prefix;
        std::string id;
        static int reg;
};

//Specialize fmt::formatter for Type
template <>
struct fmt::formatter<Register> : fmt::formatter<std::string> {
       auto format(Register &r, format_context &ctx) const ->decltype(ctx.out()) {
            return fmt::format_to(ctx.out(),"Register(id = {}, pseudo = {}",r.get_id(), r.pseudo);
       }
};


#endif
