#include "LvalueId.hpp"

extern std::string TAB;

namespace ast {

// Constructor
LvalueId::LvalueId(int lineNum, const std::string& id)
    : lineNum(lineNum), id(id) {
        spdlog::debug("inside LvalueId::{}\n",__func__);
        result = Register::create(id); 
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

std::string LvalueId::get_llvm_init() {
    spdlog::info("inside LvalueId::{}\n",__func__);
    if(dynamic_pointer_cast<ast::StructType>(this->type)) {
        spdlog::debug("{} is a struct, loading the struct address\n",this->getId());
        auto reg_llvm = this->result->get_llvm(); // llvm for the double ptr to the struct
        auto alignment = this->type->alignment();
        this->deref_result = std::make_shared<Register>();
        auto struct_ptr_llvm = this->deref_result->get_llvm(); // llvm for the ptr to the struct
        return TAB+fmt::format("{} = load ptr, ptr {}, align {}\n",struct_ptr_llvm,reg_llvm,alignment);
    } else {
        spdlog::debug("{} is not a struct, returning empty str\n",this->getId());
        this->deref_result = nullptr;
        return "";
    }
}

std::string LvalueId::get_llvm() {
    return this->result->get_llvm();
}

} // namespace ast

