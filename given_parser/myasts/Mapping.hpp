#ifndef Mapping_HPP
#define Mapping_HPP
#include <memory>
#include <string>
#include <iostream>
#include <fmt/core.h>
#include <fmt/format.h>
#include <iterator>
#include "Expression.hpp"
#include "Register.hpp"

class Register;

class Mapping {
public:
    Mapping() {};
    void addEntry(std::string var,std::shared_ptr<Register> reg);
    std::unordered_map<std::string,std::shared_ptr<Register>> entries;
    std::string display() const;
};
//Specialize fmt::formatter for Mapping
template <>
struct fmt::formatter<Mapping> : fmt::formatter<std::string> {
   auto format(const Mapping &m, format_context &ctx) const ->decltype(ctx.out()) {
       return format_to(ctx.out(),"{}",m.display());
       }
};
#endif
