#include "NewExpression.hpp"

extern std::string TAB;
extern bool use_ssa;

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
        this->type = structEntry->type;
		return this->type;
	} else {
		throw TypeException(fmt::format("No struct named {}\n",id));
	}
}

std::string NewExpression::get_llvm_init(Bblock &block) {
    spdlog::debug("inside NewExpression::{}\n",__func__);
    if(!this->result) {
        assert(!use_ssa);
        this->result = Register::create();
    }
    return TAB+fmt::format("{} = call ptr @malloc(i64 noundef {})\n",this->result->get_llvm(),this->struct_size);
}
std::string NewExpression::get_llvm(Bblock &block) {
    return this->result->get_llvm();
}

void NewExpression::resolve_uses(Bblock &block) {
    spdlog::debug("inside NewExpression::{}\n",__func__);
    this->result = Register::create();
    spdlog::debug("chose register {} for NewExpression on line {}\n",*this->result,this->getLineNum());
}

std::string NewExpression::get_ssa_init(Bblock &block) {
    spdlog::debug("inside NewExpression::{}\n",__func__);
    return this->get_llvm_init(block);
}

std::string NewExpression::get_ssa(Bblock &block) {
    spdlog::debug("inside NewExpression::{}\n",__func__);
    return this->get_llvm(block);
}

} // namespace ast

