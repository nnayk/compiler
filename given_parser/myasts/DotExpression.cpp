#include "DotExpression.hpp"

extern std::string TAB;

namespace ast {

// Constructor
DotExpression::DotExpression(int lineNum, std::shared_ptr<Expression> left, const std::string& id)
    : AbstractExpression(lineNum), left_(left), id_(id) {}

// Getter for left expression
std::shared_ptr<Expression> DotExpression::getLeft() const {
    return left_;
}

std::shared_ptr<ast::StructType> DotExpression::getLeftType() {
    spdlog::debug("inside DotExpression::{}\n",__func__);
    // if the left lvalue is NOT a struct this is a problem
    if(!(this->getLeft()->type)) {
       throw TypeException(fmt::format("Left type has not been set yet, should not have called this function!"));
    }
    auto left_type = dynamic_pointer_cast<ast::StructType>(this->getLeft()->type);
    if(!left_type) {
        throw TypeException(fmt::format("Expected type struct, found {}",*this->getLeft()->type));
    }
    return left_type;
}

// Getter for id
const std::string& DotExpression::getId() const {
    return id_;
}

std::shared_ptr<Type> DotExpression::resolveType(Env &env) {
	spdlog::info("inside DotExpression::{}\n",__func__);
	auto id = this->getId();
	this->getLeft()->resolveType(env);
    auto left_type = this->getLeftType(); 
    auto left_struct_type_name = left_type->getName();
	spdlog::debug("Current var = {},Left Lvalue of struct {} checks out!\n",id,left_struct_type_name);
    // DotExpr objects will not be in the environment (only LvalueIds will be).
	// Since at this point we know there is a outermost var (i.e. the leftmost
	// Expr in the dot expression just make sure the current id is an attribute
	// in the left struct and if so store it's type 
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

std::string DotExpression::get_llvm_init() {
    spdlog::debug("inside DotExpression::{}\n",__func__);
    spdlog::debug("id={}\n",this->getId());
    std::string llvm_ir = "";
    //spdlog::debug("left = {}\n",this->getLeft()->getId());
    llvm_ir += this->getLeft()->get_llvm_init();
    auto reg = std::make_shared<Register>();
    spdlog::debug("Got the next numerical register of {}\n",reg->get_id());
    this->result = reg;
    auto reg_llvm = this->result->get_llvm();
    assert(this->getLeft()->getDerefResult());
    auto left_reg_llvm = this->getLeft()->getDerefResult()->get_llvm();
    auto left_type = this->getLeftType(); 
    auto struct_name = left_type->getName();
    llvm_ir += TAB+fmt::format("{} = getelementptr inbounds %struct.{}, ptr {}, i32 0, i32 {}\n",reg_llvm,struct_name,left_reg_llvm,this->offset); // Yes the hardcoded i32 parts are intentional based on observing what clang does
    if(dynamic_pointer_cast<ast::StructType>(this->type)) { 
        spdlog::debug("{} is a struct, loading the struct address\n",this->getId());
        this->deref_result = std::make_shared<Register>();
        spdlog::debug("Set deref_result to {} for {}\n",this->deref_result->get_id(),this->getId());
        auto struct_ptr_llvm = this->deref_result->get_llvm();
        llvm_ir += TAB+fmt::format("{} = load ptr, ptr {}, align {}\n",struct_ptr_llvm,reg_llvm,this->type->alignment());
    } else {
        spdlog::debug("{} is not a struct, returning empty str\n",this->getId());
        this->deref_result = nullptr;
    }
    return llvm_ir;
    return "";
}

std::string DotExpression::get_llvm() {
    spdlog::debug("inside DotExpression::{}\n",__func__);
    if(dynamic_pointer_cast<ast::StructType>(this->type)) {
        spdlog::debug("struct type!\n");
        auto deref_result = this->getDerefResult();
        assert(deref_result);
        return this->deref_result->get_llvm();
    }
    return this->result->get_llvm();
}

} // namespace ast

