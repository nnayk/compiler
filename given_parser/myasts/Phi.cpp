#include "Phi.hpp"

void Phi::addEntry(std::string label, std::shared_ptr<Register> reg) {
    spdlog::debug("inside Phi::{}\n",__func__);
    assert(this->entries.find(label)==this->entries.end());
    this->entries[label] = reg;
}

std::string Phi::display() const {
    spdlog::debug("inside Phi::{}\n",__func__);
    auto out = fmt::format("{}\n","PHI:");
    out += fmt::format("assignee = {}\n",*(this->assignee));
    // Loop through the entries
    for (auto it = this->entries.begin(); it != this->entries.end(); ++it) {
        out += fmt::format("Var id: {}, Register: {}",it->first, *it->second);
    } 
    return out;
}
