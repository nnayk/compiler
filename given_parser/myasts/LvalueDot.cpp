#include "LvalueDot.hpp"
#include "LvalueId.hpp"
#include <cassert>

extern std::string TAB;

namespace ast {

// Constructor
LvalueDot::LvalueDot(int lineNum, std::shared_ptr<Lvalue> left, const std::string& id)
    : lineNum(lineNum), left(left), id(id) {}


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

std::shared_ptr<ast::StructType> LvalueDot::getLeftType() {
    // if the left lvalue is NOT a struct this is a problem
    if(!(this->left->type)) {
       throw TypeException(fmt::format("Left type has not been set yet, should not have called this function!"));
    }
    auto left_type = dynamic_pointer_cast<ast::StructType>(this->left->type);
    if(!left_type) {
        throw TypeException(fmt::format("Expected type struct, found {}",*this->left->type));
    }
    return left_type;
}

std::shared_ptr<Type> LvalueDot::resolveType(Env &env) {
	spdlog::info("inside LvalueDot::{}\n",__func__);
	auto id = this->getId();
	this->left->resolveType(env);
    auto left_type = this->getLeftType(); 
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
    return std::make_shared<NullType>(); // ctrl flow should never reac here b/c of the else stmt above
}

/* Returns the LLVM string to load the Lvalue into a register. Stores the
 * resulting register in the LvalueDot::result attribute for each portion of
 * the dot expression
*/
std::string LvalueDot::get_llvm_init(Bblock &block) {
    spdlog::debug("inside LvalueDot::{}\n",__func__);
    std::string llvm_ir = "";
    spdlog::debug("left = {}\n",this->left->getId());
    llvm_ir += this->left->get_llvm_init(block);
    auto reg = Register::create();
    spdlog::debug("Got the next numerical register of {}\n",reg->get_id());
    this->result = reg;
    auto reg_llvm = this->result->get_llvm();
    auto left_reg_llvm = this->left->getDerefResult()->get_llvm();
    auto left_type = this->getLeftType(); 
    auto struct_name = left_type->getName();
    llvm_ir += TAB+fmt::format("{} = getelementptr inbounds %struct.{}, ptr {}, i32 0, i32 {}\n",reg_llvm,struct_name,left_reg_llvm,this->offset); // Yes the hardcoded i32 parts are intentional based on observing what clang does
    if(dynamic_pointer_cast<ast::StructType>(this->type)) { 
        spdlog::debug("{} is a struct, loading the struct address\n",this->getId());
        this->deref_result = Register::create();
        auto struct_ptr_llvm = this->deref_result->get_llvm();
        llvm_ir += TAB+fmt::format("{} = load ptr, ptr {}, align {}\n",struct_ptr_llvm,reg_llvm,this->getType()->alignment());
    } else {
        spdlog::debug("{} is not a struct, returning empty str\n",this->getId());
        this->deref_result = nullptr;
    }
    return llvm_ir;
}

std::string LvalueDot::get_llvm(Bblock &block) {
    spdlog::debug("inside LvalueDot::{}\n",__func__);
    spdlog::debug("id={}, llvm = {}\n",this->getId(),this->result->get_llvm());
    if(dynamic_pointer_cast<ast::StructType>(this->type)) {
        spdlog::debug("struct type!\n");
        auto deref_result = this->getDerefResult();
        assert(deref_result);
        return this->deref_result->get_llvm();
    }
    return this->result->get_llvm();
}

std::string LvalueDot::get_ssa_init(Bblock &block) {
	spdlog::debug("inside LvalueDot::{}\n",__func__);
    return this->get_llvm_init(block);
}

std::string LvalueDot::get_arm_init(Bblock &block) {
    spdlog::debug("inside LvalueDot::{}\n",__func__);
    std::string arm = "";
    return arm;
}

std::string LvalueDot::get_ssa(Bblock &block) {
	spdlog::debug("inside LvalueDot::{}\n",__func__);
    return this->get_llvm(block);
}

std::string LvalueDot::get_topmost_id() {
	spdlog::debug("inside LvalueDot::{}\n",__func__);
	auto curr = shared_from_this();
    while(true) {
        auto left = curr->getLeft();
        if(auto lvalue_id = dynamic_pointer_cast<LvalueId>(curr)) {
            return lvalue_id->getId();
        } else {
            curr = dynamic_pointer_cast<LvalueDot>(curr->getLeft());
            assert(curr);
        }
    }
}

void LvalueDot::resolve_def(std::string &source_immediate) {
    spdlog::debug("inside LvalueDot::{}\n",__func__);
    // No need to create a register for the attribute, just want to resolve the "outermost" struct var...
    this->getLeft()->resolve_def(source_immediate);
}

} // namespace ast

