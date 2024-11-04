#include "Mapping.hpp"
#include <spdlog/spdlog.h>


void Mapping::addEntry(std::string var,std::shared_ptr<Register> reg) {
    spdlog::debug("inside Mapping::{}\n",__func__);
    spdlog::debug("Adding entry from var {} to register {}\n",var,*reg);
    entries[var] = reg;
}
