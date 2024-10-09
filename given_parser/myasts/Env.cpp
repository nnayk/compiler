#include "Env.hpp"

Env::Env() {}

void Env::addBinding(std::string &key, const Entry& entry) {
    this->bindings[key].push_back(entry);
}
