#include "ReturnStatement.hpp"
#include "TypeException.hpp"
#include <typeinfo>

namespace ast {

// Constructor that calls the base class constructor
ReturnStatement::ReturnStatement(int lineNum, std::shared_ptr<ast::Expression> expression)
    : AbstractStatement(lineNum), expression(expression) {}

void ReturnStatement::typecheck(Env &env, Function &f) {
    auto actual_ret_type = this->expression->resolveType(env);
    auto expected_ret_type = f.retType;
    if(typeid(actual_ret_type) == typeid(expected_ret_type)) {
        throw TypeException(fmt::format("Expected return type {} for function {}, got {} instead",*expected_ret_type,f.name,*actual_ret_type));
    }
}

} // namespace ast

