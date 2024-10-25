#include "Register.hpp"
#include <spdlog/spdlog.h>

int Register::reg = 0;
std::string Register::LOCAL_PREFIX = "%";
std::string Register::GLOBAL_PREFIX = "@";
std::unordered_map<std::string,std::shared_ptr<Register>> all_regs;
Register::Register(const std::string &id,const bool &is_global) :  id(id) {       
    auto prefix = Register::LOCAL_PREFIX;
    if(is_global) prefix = Register::GLOBAL_PREFIX;
    this->prefix = prefix;
    spdlog::info("inside Register::{}\n",__func__);
    all_regs[id] = std::make_shared<Register>(*this);
    if(id==std::to_string(reg)) reg++;
}

std::string Register::get_id() {
    return this->id;
}

std::string Register::get_prefix() {
    return this->prefix;
}

void Register::set_global_prefix() {
    this->prefix = Register::GLOBAL_PREFIX;
}

std::string Register::get_llvm() {
    return this->prefix+this->id;
}
