#ifndef ENV_HPP
#define ENV_HPP
#include <memory>
#include <string>
#include "Type.hpp"

class Env;

class Entry {
public:
    ast::Type type;
    // Constructor
    Entry(const ast::Type &t);
};

class StructEntry : public Entry {
public:
    std::shared_ptr<Env> attrEnv; // used to track struct attributes
    // Constructor
    StructEntry(const ast::Type &t): Entry(t) {}
};

class Env {
public:
    std::unordered_map<std::string,std::vector<Entry>> bindings;
    // Constructor
    Env();
    void addBinding(const std::string &key,const Entry& entry);
};
#endif
