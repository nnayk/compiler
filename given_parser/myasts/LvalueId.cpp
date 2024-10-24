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
    try {
        std::shared_ptr<Entry> entry = env.bindings.at(this->getId());
        this->type = entry->type;
        return this->type;
	} catch (const std::out_of_range& e) {
		throw TypeException(fmt::format("LvalueId {} not found in environment",this->getId()));
	}
}

std::string LvalueId::get_llvm() const {
    return "";
}

} // namespace ast

