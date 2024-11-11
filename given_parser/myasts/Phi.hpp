#ifndef __PHI__HPP__
#define __PHI__HPP__
#include "Register.hpp"

class Phi {
    public:
        std::unordered_map<std::string,std::shared_ptr<Register>> entries;
        std::shared_ptr<Register> assignee = nullptr; // register that's assigned to this phi
        std::shared_ptr<Bblock> block = nullptr; // block that contains this phi
        Phi() {};
        void addEntry(std::string label,std::shared_ptr<Register> reg);
};
#endif
