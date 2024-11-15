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

std::string Phi::get_ssa() {
    spdlog::debug("inside Phi::{}\n",__func__);
    std::string ssa = "phi ";
    spdlog::debug("Considering phi with {} entries\n",this->entries.size());
    for (auto it = this->entries.begin(); it != this->entries.end(); ++it) {
        auto label = it->first;
        auto reg = it->second;
        spdlog::debug("label = {}\n",label);
        spdlog::debug("assignee reg = {}\n",*reg);
        ssa += 
    } 
    return ssa;
}
