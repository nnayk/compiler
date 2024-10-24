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
        std::string id;
        std::shared_ptr<ast::Type> content_type; // type of the value in register
        std::vector<std::shared_ptr<ast::Expression>> references; // for quickly updating a register's usage for SSA trivial phi deletion
        //TODO: add pointers to expressions for every place the register is used
        Register(const std::string &id = std::to_string(reg));
    private:
        static int reg;
};


#endif
