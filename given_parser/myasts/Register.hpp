#ifndef REGISTER_HPP
#define REGISTER_HPP
#include <string>
#include <memory>
#include "Expression.hpp"
#include "Type.hpp"

class Register;
// global map of all registers
class Register {
    public:
        static std::string LOCAL_PREFIX;
        static std::string GLOBAL_PREFIX;
        std::shared_ptr<ast::Type> content_type; // type of the value in register
        std::vector<std::shared_ptr<ast::Expression>> references; // for quickly updating a register's usage for SSA trivial phi deletion
        //TODO: add pointers to expressions for every place the register is used
        Register(const std::string &id = std::to_string(reg),const bool &is_global=false);
        void set_global(); // Discovered that an ID was global when resolving type and now must adjust the register prefix
        std::string get_id();
        std::string get_prefix();
        void set_global_prefix();
        std::string get_llvm();
    private:
        std::string prefix;
        std::string id;
        static int reg;
};


#endif
