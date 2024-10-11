#include "Env.hpp"

Entry::Entry(const ast::Type &t): type(t) {}
Env::Env() {}

void Env::addBinding(std::string &key, const Entry& entry) {
    this->bindings[key].push_back(entry);
}
