#ifndef Mapping_HPP
#define Mapping_HPP
#include <memory>
#include <string>
#include <iostream>
#include <fmt/core.h>
#include <fmt/format.h>
#include "Expression.hpp"
#include "Register.hpp"


class Mapping {
public:
    Mapping() {};
    void addEntry(std::string var,std::shared_ptr<Register> reg);
private:
    std::unordered_map<std::string,std::shared_ptr<Register>> entries;
};
#endif
