#include "Env.hpp"

Entry::Entry(std::shared_ptr<ast::Type> t): type(t) {}
Env::Env() {}

void Env::addBinding(const std::string &key, std::shared_ptr<Entry> entry) {
    this->bindings[key] = entry;
}

std::shared_ptr<Entry> Env::lookup(const std::string &id) {
    auto iter = this->bindings.find(id); 
    if(iter == this->bindings.end()) {
        return nullptr;
    } else {
        return iter->second;
    }
}
