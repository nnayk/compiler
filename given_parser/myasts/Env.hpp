#ifndef ENV_HPP
#define ENV_HPP
#include <memory>
#include <string>
#include "Type.hpp"

class Env;

class Entry {
public:
    int free_1; // free integer -- ex. can be used to track index count for
                // struct attributes
    
    ast::Type type;
    std::shared_ptr<Env> attrEnv; // used to track struct attributes
    // Constructor
    Entry(const ast::Type &t);
};
class Env {
public:
    std::unordered_map<std::string,std::vector<Entry>> bindings;
    // Constructor
    Env();
    void addBinding(std::string &key,const Entry& entry);
};
#endif
