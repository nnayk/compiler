#include "Mapping.hpp"
#include <spdlog/spdlog.h>


void Mapping::addEntry(std::string var,std::shared_ptr<Register> reg) {
    spdlog::debug("inside Mapping::{}\n",__func__);
    spdlog::debug("Adding entry from var {} to register {}\n",var,*reg);
    entries[var] = reg;
}

std::string Mapping::display() const {
    spdlog::debug("inside Mapping::{}\n",__func__);
    auto out = fmt::format("Mapping (# entries = {}:\n",this->entries.size());
    for(auto it = this->entries.begin(); it != this->entries.end(); ++it) {
        out += fmt::format("Entry {}: var = {}, reg = {}\n", std::distance(this->entries.begin(),it),it->first,it->second->get_id());
    }
    return out;
}
