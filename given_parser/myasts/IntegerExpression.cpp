#include "IntegerExpression.hpp"

namespace ast {

// Constructor
IntegerExpression::IntegerExpression(int lineNum, const std::string& value)
    : AbstractExpression(lineNum), value(value) {}

// Getter for the value
std::string IntegerExpression::getValue() const {
    return value;
}

std::shared_ptr<Type> IntegerExpression::resolveType(Env &env) {
    this->type = std::make_shared<IntType>();
    return this->type;
}

std::string IntegerExpression::get_llvm(Bblock &block) {
    return this->value;
}

void IntegerExpression::resolve_uses(Bblock &block) {
    spdlog::debug("inside IntegerExpression::{}\n",__func__);
    auto id = this->get_llvm(block);
    this->result = Register::create(id,false,true);
}

} // namespace ast

