#include "LvalueId.hpp"

extern std::string TAB;
extern bool use_ssa;

namespace ast {

// Constructor
LvalueId::LvalueId(int lineNum, const std::string& id)
    : lineNum(lineNum), id(id) {
        spdlog::debug("inside LvalueId::{}\n",__func__);
        if(!use_ssa) result = Register::create(id); // TODO: change this!!! should only be for non-ssa (basically move this to get_llvm_init)
        //TODO: Think content type is not needed in Register class since I'm resolving type and storing it as an attr in Lvalue itself
        //result->content_type =  this->type;
    }

// Getter methods
int LvalueId::getLineNum() const {
    return lineNum;
}

std::string LvalueId::getId() const {
    return id;
}

/*
Resolve the Lvalue to a base type. If not possible raise an exception.
*/
std::shared_ptr<Type> LvalueId::resolveType(Env &env) {
    spdlog::debug("inside LvalueId::{}\n",__func__);
    auto id = this->getId();
    auto it = env.lookup(id);
    //TODO: abstract away the lookup logic. call env.lookup() and 
    // use the returned entry to set this->type and call this->result-.set_globa... if needed (entry will have a flag to indicate local,param,or global)
    // look in local env
    if(env.bindings.find(id) != env.bindings.end()) {
        auto it = env.bindings.find(id);
        this->type = it->second->type;
		spdlog::debug("Local env: Found {} of type {}",id,*this->type);
    // look in global var env
    } else if(globalsTLE.bindings.find(id) != globalsTLE.bindings.end()) {
        auto it = globalsTLE.bindings.find(id); 
        this->type = it->second->type;
		spdlog::debug("Global env: Found {} of type {}",id,*this->type);
        // NOTE: p sure this will cause a seg fault since result wouldn't have been set yet...instead create an attr for LvalueId to mark as global...
        this->result->set_global_prefix();
    // look in global struct env
    } else if(structTLE.bindings.find(id) != structTLE.bindings.end()) {
		spdlog::debug("Struct env: Found {} of type {}",id,*this->type);
        auto it = structTLE.bindings.find(id); 
        this->type = it->second->type;
        this->result->set_global_prefix();
    } else {
        throw TypeException(fmt::format("LvalueId {} not found in environment",this->getId()));
    }
    return this->type;
}

std::string LvalueId::get_llvm_init(Bblock &block) {
    spdlog::info("inside LvalueId::{}\n",__func__);
    if(dynamic_pointer_cast<ast::StructType>(this->type)) {
        spdlog::debug("{} is a struct, loading the struct address\n",this->getId());
        auto reg_llvm = this->result->get_llvm(); // llvm for the double ptr to the struct
        auto alignment = this->type->alignment();
        this->deref_result = Register::create();
        auto struct_ptr_llvm = this->deref_result->get_llvm(); // llvm for the ptr to the struct
        return TAB+fmt::format("{} = load ptr, ptr {}, align {}\n",struct_ptr_llvm,reg_llvm,alignment);
    } else {
        spdlog::debug("{} is not a struct, returning empty str\n",this->getId());
        this->deref_result = nullptr;
        return "";
    }
}

std::string LvalueId::get_llvm(Bblock &block) {
	spdlog::debug("inside LvalueId::{}\n",__func__);
    return this->result->get_llvm();
}

std::string LvalueId::get_ssa(Bblock &block) {
	spdlog::debug("inside LvalueId::{}\n",__func__);
    return this->result->get_llvm();
}

std::string LvalueId::get_ssa_init(Bblock &block) {
	spdlog::debug("inside LvalueId::{}\n",__func__);
    return this->get_llvm_init(block);
}

std::string LvalueId::get_arm_init(Bblock &block) {
    spdlog::debug("inside LvalueId::{}\n",__func__);
    std::string arm = "";
    // TODO: extra instructions for struct needed (i.e. load its address)
    return arm;
}

void LvalueId::resolve_def(std::string &source_immediate) {
    spdlog::debug("inside LvalueId::{}\n",__func__);
    //assert(!this->result);
    spdlog::debug("source_immediate = {}\n",source_immediate);
    if(source_immediate.length()) {
        // TODO: Here I assume we have a local var...but it could be a global very well. ctrl+f for "NOTE" in this file to see my idea about adding an "is_global" field to Lvalue..
        this->result = Register::create(source_immediate,false,true);
    } else {
        this->result = Register::create();
    }
}



} // namespace ast

