#include "Register.hpp"

int Register::reg = 0;
std::unordered_map<std::string,std::shared_ptr<Register>> all_regs;
Register::Register(const std::string &id ) : id(id) {         
    all_regs[id] = std::make_shared<Register>(*this);
    if(id==std::to_string(reg)) reg++;
}
