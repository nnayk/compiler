#include "Lvalue.hpp"

namespace ast {
std::shared_ptr<ast::Type> Lvalue::getType() {
    spdlog::debug("inside Lvalue::{}\n",__func__);
    return this->type;
}

}
