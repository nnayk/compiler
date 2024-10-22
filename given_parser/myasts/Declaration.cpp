#include "Declaration.hpp"
#include <spdlog/spdlog.h>
#include "TypeException.hpp"

namespace ast {

// Constructor implementation
Declaration::Declaration(int lineNum, std::shared_ptr<Type> type, const std::string& name)
    : lineNum_(lineNum), type_(type), name_(name) {}

// Getter for line number
int Declaration::getLineNum() const {
    return lineNum_;
}

// Returns the llvm IR for accessing the variable
// There are differences based on if the var is local
// or global:
// 1. Local: %var
// 2. Global: @var
std::string Declaration::get_llvm() {
    return "";
}

std::string Declaration::get_llvm_init(const std::string &var_type="local") {
    spdlog::debug("Declaration::{}: var name = {}\n",__func__,this->getName());
    std::string llvm_str;
    auto type = this->getType();
    if(var_type == "global") {
        llvm_str = fmt::format("@{} = global {} {}, align {}",this->getName(),
                   type->get_llvm(), type->default_val(), type->alignment() );
    } else if(var_type == "local") {
        llvm_str = fmt::format("%{} = alloca {}, align {}\n",this->getName(),type->get_llvm(),type->alignment());
    } else if(var_type == "param") {
        llvm_str = fmt::format("{} noundef %{}",type->get_llvm(),this->getName());
    } else {
        throw TypeException(fmt::format("Declaration::{}: Unknown var type {}\n",__func__,var_type));        
    }
    return llvm_str;
}

// Getter for type
std::shared_ptr<Type> Declaration::getType() const {
    return type_;
}

// Getter for name
const std::string& Declaration::getName() const {
    return name_;
}
} // namespace ast


