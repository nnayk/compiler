#include "Env.hpp"

Entry::Entry(std::shared_ptr<ast::Type> t): type(t) {}
Env::Env() {}

void Env::addBinding(const std::string &key, std::shared_ptr<Entry> entry) {
    this->bindings[key].push_back(entry);
}
