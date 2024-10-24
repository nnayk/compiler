#include "LvalueId.hpp"

namespace ast {

// Constructor
LvalueId::LvalueId(int lineNum, const std::string& id)
    : lineNum(lineNum), id(id) {
        result = std::make_shared<Register>(id);
        result->content_type =  this->type;
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
    // look in global struct env
    } else if(structTLE.bindings.find(id) != structTLE.bindings.end()) {
		spdlog::debug("Struct env: Found {} of type {}",id,*this->type);
        auto it = structTLE.bindings.find(id); 
        this->type = it->second->type;
    } else {
        throw TypeException(fmt::format("LvalueId {} not found in environment",this->getId()));
    }
    return this->type;
}

std::string LvalueId::get_llvm() const {
    return "";
}

} // namespace ast

