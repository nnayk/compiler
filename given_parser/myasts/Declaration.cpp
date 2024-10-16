#include "Declaration.hpp"
#include <spdlog/spdlog.h>

namespace ast {

// Constructor implementation
Declaration::Declaration(int lineNum, std::shared_ptr<Type> type, const std::string& name)
    : lineNum_(lineNum), type_(type), name_(name) {}

// Getter for line number
int Declaration::getLineNum() const {
    return lineNum_;
}

std::string Declaration::get_llvm() {
    return this->getName();
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


