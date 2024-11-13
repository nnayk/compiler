#include "utils.hpp"

bool is_immediate(std::shared_ptr<ast::Expression> e) {
    spdlog::debug("inside is_immediate\n");
    return (
            (dynamic_pointer_cast<ast::IntegerExpression>(e) != nullptr) 
            || (dynamic_pointer_cast<ast::TrueExpression>(e) != nullptr) 
            || (dynamic_pointer_cast<ast::FalseExpression>(e) != nullptr)
           ); 
}
