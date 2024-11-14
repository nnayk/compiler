#include "Register.hpp"
#include <spdlog/spdlog.h>

int Register::reg = 1;
std::string Register::LOCAL_PREFIX = "%";
std::string Register::GLOBAL_PREFIX = "@";
std::unordered_map<std::string,std::shared_ptr<Register>> all_regs;
Register::Register(const std::string &id,const bool &is_global,const bool &is_pseudo) :  id(id) {       
    auto prefix = Register::LOCAL_PREFIX;
    if(is_global) prefix = Register::GLOBAL_PREFIX;
    this->pseudo = is_pseudo;
    this->prefix = prefix;
    spdlog::info("inside Register::{}\n",__func__);
    if(id==std::to_string(reg) && !is_pseudo) reg++;
}

std::shared_ptr<Register> Register::create(const std::string &id,const bool&is_global,const bool &is_pseudo) {
    spdlog::debug("inside Register::{}\n",__func__);
    spdlog::debug("id={},is_global={},is_pseudo={}\n",id,is_global,is_pseudo);
    if(!is_pseudo && all_regs.find(id) != all_regs.end()) {
        spdlog::debug("register {} already exists!\n",id);
        //assert(id=="_ret"); // rn this is the only case where the same id can be passed to create I believe
        return all_regs[id];
    }
    auto reg = std::shared_ptr<Register>(new Register(id,is_global,is_pseudo));
    if(!is_pseudo) all_regs[id] = reg->shared_from_this();
    return reg;
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
    //this->references.push_back(e);
    if(this->pseudo) return this->id;
    else return this->prefix+this->id;
}
