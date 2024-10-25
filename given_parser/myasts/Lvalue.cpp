#include "Lvalue.hpp"

namespace ast {
std::shared_ptr<ast::Type> Lvalue::getType() {
    spdlog::debug("inside Lvalue::{}\n",__func__);
    return this->type;
}

std::shared_ptr<Register> Lvalue::getResult() {
    return this->result;
}

std::shared_ptr<Register> Lvalue::getDerefResult() {
    return this->deref_result;
}

}
