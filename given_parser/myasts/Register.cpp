#include "Register.hpp"
#include <spdlog/spdlog.h>

int Register::reg = 0;
std::unordered_map<std::string,std::shared_ptr<Register>> all_regs;
Register::Register(const std::string &id ) : id(id) {        
    spdlog::info("inside Register::{}\n",__func__);
    all_regs[id] = std::make_shared<Register>(*this);
    if(id==std::to_string(reg)) reg++;
}
