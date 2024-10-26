#include "NewExpression.hpp"

extern std::string TAB;
namespace ast {

// Constructor
NewExpression::NewExpression(int lineNum, const std::string& id)
    : AbstractExpression(lineNum), id(id) {}

// Getter method for id
const std::string& NewExpression::getId() const {
    return id;
}

std::shared_ptr<ast::Type> NewExpression::resolveType(Env &env) {
	spdlog::debug("inside NewExpression::{}\n",__func__);
	auto id = this->getId();
	if(structTLE.bindings.find(id) != structTLE.bindings.end()) {
		auto it = structTLE.bindings.find(id);
		auto structEntry = dynamic_pointer_cast<StructEntry>(it->second);
		assert(structEntry);
		this->struct_size = structEntry->size;
		return structEntry->type;
	} else {
		throw TypeException(fmt::format("No struct named {}\n",id));
	}
}

std::string NewExpression::get_llvm_init() {
    spdlog::debug("inside NewExpression::{}\n",__func__);
    this->result = Register::create();
    return TAB+fmt::format("{} = call ptr @malloc(i64 noundef {})\n",this->result->get_llvm(),this->struct_size);
}
std::string NewExpression::get_llvm() {
    return this->result->get_llvm();
}


} // namespace ast

