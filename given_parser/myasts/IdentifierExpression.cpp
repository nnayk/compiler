#include "IdentifierExpression.hpp"
#include <cassert>

extern std::string TAB;
namespace ast {

// Constructor
IdentifierExpression::IdentifierExpression(int lineNum, const std::string& id)
    : AbstractExpression(lineNum), id(id) {
        spdlog::debug("IdentifierExpression::{}\n",__func__);
        this->result = Register::create(id);
    }

// Getter for the identifier
const std::string& IdentifierExpression::getId() const {
    return id;
}

std::shared_ptr<Type> IdentifierExpression::resolveType(Env &env) {
    spdlog::debug("inside IdentifierExpression::{}\n",__func__);
    auto id = this->getId();
    spdlog::debug("id = {},lineNum={}\n",id,this->getLineNum());
    auto entry = env.lookup(id);
    if(entry) {
        this->type = entry->type;
        spdlog::debug("set type for id {} to {}\n",id,*this->type);
        this->scope = entry->scope;
        return this->type; 
    } else {
        throw TypeException(fmt::format("Unknown identifier {}",id));
    }
}

std::string IdentifierExpression::get_llvm_init() {
    spdlog::debug("inside IdentifierExpression::{}\n",__func__);
    spdlog::debug("id={}\n",id);
    if(this->scope == 1) return "";
    this->deref_result = Register::create();
    auto deref_llvm = this->deref_result->get_llvm();
    spdlog::debug("deref_llvm = {}\n",deref_llvm);
    spdlog::debug("after");
    auto type_llvm = this->type->get_llvm();
    spdlog::debug("type llvm = {}\n",type_llvm);
    auto alignment_llvm = this->type->alignment();
    spdlog::debug("alignment llvm = {}\n",alignment_llvm);
    auto result_llvm = this->result->get_llvm();
    spdlog::debug("result llvm = {}\n",result_llvm);
    assert(this->result);
    assert(this->getResult());
    assert(this->deref_result);
    assert(this->getDerefResult());
    return TAB+fmt::format("{} = load {}, ptr {}, align {}\n",deref_llvm,type_llvm,result_llvm,alignment_llvm);
}

std::string IdentifierExpression::get_llvm() {
    spdlog::debug("inside IdentifierExpression::{}\n",__func__);
	auto deref_result = this->deref_result;
    if(deref_result) {
        return this->deref_result->get_llvm();
    } else {
        assert(this->scope==1);
        return this->result->get_llvm();
    }
}

} // namespace ast

