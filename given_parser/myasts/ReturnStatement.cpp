#include "ReturnStatement.hpp"
#include "AssignmentStatement.hpp"
#include "LvalueId.hpp"
#include "TypeException.hpp"
#include <typeinfo>

extern std::string TAB;

namespace ast {

// Constructor that calls the base class constructor
ReturnStatement::ReturnStatement(int lineNum, std::shared_ptr<ast::Expression> expression)
    : AbstractStatement(lineNum), expression(expression) {}

void ReturnStatement::typecheck(Env &env, Function &f) {
    spdlog::debug("inside ReturnStatement::{}\n",__func__);
    auto actual_ret_type = this->expression->resolveType(env);
    assert(this->expression->type);
    auto expected_ret_type = f.retType;
    if(typeid(actual_ret_type) != typeid(expected_ret_type)) {
        throw TypeException(fmt::format("Expected return type {} for function {}, got {} instead",*expected_ret_type,f.name,*actual_ret_type));
    }
    this->retType = actual_ret_type;
}

std::string ReturnStatement::get_llvm(Bblock &block) {
    spdlog::debug("inside ReturnStatement::{}\n",__func__);
    assert(this->expression->type);
    std::string llvm = this->expression->get_llvm_init(block);
    spdlog::debug("llvm={}\n",llvm);
    llvm += TAB+fmt::format("ret {} {}\n",this->retType->get_llvm(),this->expression->get_llvm(block));
    return llvm;
}

std::string ReturnStatement::get_ssa(Bblock &block) {
    spdlog::debug("inside ReturnStatement::{}\n",__func__);
    return this->get_llvm(block);
}

std::vector<std::shared_ptr<Bblock>> ReturnStatement::get_cfg() {
    spdlog::debug("inside ReturnStatement::{}\n",__func__);
    auto lvalue = std::make_shared<LvalueId>(this->getLineNum(),"_ret");
    assert(this->expression->type);
    assert(this->retType);
    lvalue->type = this->retType;
    std::shared_ptr<AssignmentStatement> assignment = std::make_shared<AssignmentStatement>(this->getLineNum(),lvalue,this->expression);
    std::vector<std::shared_ptr<Bblock>> blocks = assignment->get_cfg();
    return blocks;
}

void ReturnStatement::resolve_def_uses(Bblock &block) {
    spdlog::debug("inside ReturnStatement::{}\n",__func__);
    this->expression->resolve_uses(block);    
}



} // namespace ast

