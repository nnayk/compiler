#include "Phi.hpp"

void Phi::addEntry(std::string label, std::shared_ptr<Register> reg) {
    spdlog::debug("inside Phi::{}\n",__func__);
    assert(this->entries.find(label)==this->entries.end());
    this->entries[label] = reg;
}
