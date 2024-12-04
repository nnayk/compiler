#include "IdentifierExpression.hpp"
#include "InvalidUseException.hpp"
#include <cassert>

extern std::string TAB;
extern bool use_ssa;
namespace ast {

// Constructor
IdentifierExpression::IdentifierExpression(int lineNum, const std::string& id)
    : AbstractExpression(lineNum), id(id) {
        spdlog::debug("IdentifierExpression::{}\n",__func__);
        // TODO: move this to get_llvm as it's inaccurate for ssa
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

std::string IdentifierExpression::get_llvm_init(Bblock &block) {
    spdlog::debug("inside IdentifierExpression::{}\n",__func__);
    spdlog::debug("id={}\n",id);
    if(use_ssa) {
        spdlog::debug("in ssa mode, calling get_ssa_init\n");
        return this->get_ssa_init(block);
    }
    spdlog::debug("in non-ssa mode, generating llvm init\n");
    if(this->scope == 1) {
        spdlog::debug("{} is a param (already in a register), no llvm init\n",id);
        return "";
    }
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

std::string IdentifierExpression::get_llvm(Bblock &block) {
    spdlog::debug("inside IdentifierExpression::{}\n",__func__);
    if(use_ssa) return this->get_ssa(block);
	auto deref_result = this->deref_result;
    if(deref_result) {
        return this->deref_result->get_llvm();
    } else {
        assert(this->scope==1);
        return this->result->get_llvm();
    }
}

std::string IdentifierExpression::get_ssa_init(Bblock &block) {
    spdlog::debug("inside IdentifierExpression:{}\n",__func__);
    return "";
}

std::string IdentifierExpression::get_ssa(Bblock &block) {
    spdlog::debug("inside IdentifierExpression::{}\n",__func__);
    spdlog::debug("line = {}\n",this->getLineNum());
    if(this->result) {
        return this->result->get_llvm();
    } else {
        throw InvalidUseException(fmt::format("Use of uninitialized var {}\n",this->getId()));
    }
    return "";
}

std::string IdentifierExpression::get_arm_init(Bblock &block) {
    spdlog::debug("inside IdentifierExpression::{}\n",__func__);
    std::string arm = fmt::format("arm {}, [sp, {}]",this->get_arm(block),this->stack_offset);
    return arm;
}

std::string IdentifierExpression::get_arm(Bblock &block) {
    spdlog::debug("inside IdentifierExpression::{}\n",__func__);
    spdlog::debug("line = {}\n",this->getLineNum());
    if(this->result) {
        return this->result->get_arm();
    } else {
        throw InvalidUseException(fmt::format("Use of uninitialized var {}\n",this->getId()));
    }
    return "";
}

void IdentifierExpression::resolve_uses(Bblock &block) {
    spdlog::debug("inside IdentifierExpression::{}\n",__func__);
   auto reg = block.lookup(shared_from_this());   
   spdlog::debug("resolved IdExpression {} on line {} to register {}\n",this->getId(),this->getLineNum(),*reg);
   this->result = reg;
   this->result->add_exp(shared_from_this());
}

} // namespace ast

