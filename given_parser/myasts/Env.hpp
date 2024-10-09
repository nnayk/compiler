#include <memory>
#include <string>

class Entry {
public:
    int free_1; // free integer -- ex. can be used to track index count for
                // struct attributes
    // Constructor
    Entry();
};
class Env {
public:
    std::unordered_map<std::string,std::vector<Entry>> bindings;
    // Constructor
    Env();
    void addBinding(std::string &key,const Entry& entry);
};
