#include "Phi.hpp"
#include "IdentifierExpression.hpp"
#include <unordered_set>

extern std::string TAB;

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
    spdlog::debug("data type = {}\n",*this->type);
    std::string ssa = TAB+fmt::format("{} = ",this->assignee->get_llvm());
    ssa += fmt::format("phi {} ",this->type->get_llvm());
    spdlog::debug("Considering phi with {} entries\n",this->entries.size());
    for (auto it = this->entries.begin(); it != this->entries.end(); ++it) {
        auto label = it->first;
        auto reg = it->second;
        spdlog::debug("label = {}\n",label);
        spdlog::debug("assignee reg = {}\n",*reg);
        ssa += fmt::format("[ {}, %{} ],",reg->get_llvm(),label);
    } 
    spdlog::debug("phi ssa = {}\n",ssa);
    assert(ssa[ssa.size()-1]==',');
    return ssa.substr(0,ssa.size()-1)+"\n";
}

std::shared_ptr<Register> Phi::is_trivial() {
    spdlog::debug("inside Phi::{}\n",__func__);
    std::unordered_set<std::shared_ptr<Register>> regs;
    // TODO: consider each register in entries and if they're all the same then assignee is trivial. Otherwise return null
    //assert(regs.size()==1);
    //return *regs.begin();
    return nullptr;
}
