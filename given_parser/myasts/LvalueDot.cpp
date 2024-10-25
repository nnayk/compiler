#include "LvalueDot.hpp"

namespace ast {

// Constructor
LvalueDot::LvalueDot(int lineNum, std::shared_ptr<Lvalue> left, const std::string& id)
    : lineNum(lineNum), left(left), id(id) {
            result = std::make_shared<Register>(id);
}

// Getter methods
int LvalueDot::getLineNum() const {
    return lineNum;
}

std::shared_ptr<Lvalue> LvalueDot::getLeft() const {
    return left;
}

std::string LvalueDot::getId() const {
    return id;
}

std::shared_ptr<Type> LvalueDot::resolveType(Env &env) {
	spdlog::info("inside LvalueDot::{}\n",__func__);
	auto id = this->getId();
    auto left_type = dynamic_pointer_cast<ast::StructType>(this->left->resolveType(env));
    // if the left lvalue is NOT a struct this is a problem
    if(!(left_type)) {
       throw TypeException(fmt::format("Expected left of {} to be StructType, found type: {}\n",id, *this->left->resolveType(env))); 
    }
	auto left_struct_type_name = left_type->getName();
	spdlog::debug("Current var = {},Left Lvalue of struct {} checks out!\n",id,left_struct_type_name);
    // LvalueDot objects will not be in the environment (only LvalueIds will be).
	// Since at this point we know there is a outermost var (i.e. the leftmost
	// Lvalue in the dot expression just make sure the current id is an attribute
	// in the left Lvalue struct and if so store it's type 
    if(structTLE.bindings.find(left_struct_type_name) != structTLE.bindings.end()) {
		auto struct_entry = dynamic_pointer_cast<StructEntry>(structTLE.bindings.find(left_struct_type_name)->second);
		if(!struct_entry) {
		   // TODO: change to ImpossibleException
		   throw TypeException(fmt::format("Failed to cast entry in structTLE to StructEntry ptr")); 
		}
		auto attrEnv = struct_entry->attrEnv;
		if(attrEnv->bindings.find(id) != attrEnv->bindings.end()) {
			auto attr_entry = dynamic_pointer_cast<AttrEntry>(attrEnv->bindings.find(id)->second);
			if(!attr_entry) {
			   // TODO: change to ImpossibleException
			   throw TypeException(fmt::format("Failed to cast entry in attrEnv to AttrEntry ptr"));
			} 
			this->type = attr_entry->type;
			this->offset = attr_entry->offset;
			return this->type;
		} else {
			throw TypeException(fmt::format("No attribute {} in struct {}",id,left_type->getName()));
		}	
	} else {
	   // TODO: change this to a new Exception class ImpossibleException
       throw TypeException(fmt::format("This should be impossible b/c I already typechecked left lvalue"));
	}   				
    return std::make_shared<NullType>();
}

/* Returns the LLVM string to load the Lvalue into a register. Stores the
 * resulting register in the LvalueDot::result attribute for each portion of
 * the dot expression
*/
std::string LvalueDot::get_llvm_init() {
    spdlog::debug("inside LvalueDot::{}\n",__func__);
    std::string llvm_ir = "";
    spdlog::debug("left = {}\n",this->left->getId());
    llvm_ir += this->left->get_llvm_init();
    auto reg = std::make_shared<Register>();
    spdlog::debug("Got the next numerical register of {}\n",reg->get_id());
    this->result = reg;
    //TODO: implement
    return llvm_ir;
}

std::string LvalueDot::get_llvm() {
    return this->result->get_llvm();
}

} // namespace ast

