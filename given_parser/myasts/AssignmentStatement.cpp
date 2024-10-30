#include "AssignmentStatement.hpp"
#include "Types.hpp"
#include "InvocationExpression.hpp"
#include "BinaryExpression.hpp"
extern std::string TAB;

namespace ast {

// Constructor definition
AssignmentStatement::AssignmentStatement(int lineNum, std::shared_ptr<Lvalue> target, std::shared_ptr<Expression> source)
    : AbstractStatement(lineNum), target(target), source(source) {}

// Getter for target
std::shared_ptr<Lvalue> AssignmentStatement::getTarget() const {
    return target;
}

// Getter for source
std::shared_ptr<Expression> AssignmentStatement::getSource() const {
    return source;
}

// Returns the non-llvm SSA string of instructions for the assignment
std::string AssignmentStatement::get_llvm() {
	spdlog::debug("inside AssignmentStatement:{}\n",__func__);
    spdlog::debug("lineNum = {}\n",this->getLineNum());
	std::string llvm_ir = "";
    //spdlog::debug("target = {}\n",*this-target);
    spdlog::debug("source = {}\n",*(this->source));
    assert(this->source);
    assert(this->target);
    assert(this->target->type);
    assert(this->source->type);
	//TODO: impleement get_llvm_init for expr + lvalue classes
	std::string target_llvm_init = this->target->get_llvm_init();
    spdlog::debug("Got target llvm for id {}: {}\n",this->target->getId(),target_llvm_init);
    spdlog::debug("Target id = {}, type = {}\n",this->target->getId(), *this->target->type);
    std::string source_llvm_init = this->source->get_llvm_init();
    spdlog::debug("Got source llvm: {}\n",source_llvm_init);
	llvm_ir += target_llvm_init;
	llvm_ir += source_llvm_init;
	//Add llvm ir to perform the assignment
	//Note: Since I'm allocating all local vars on the stack (and global vars+
    // structs are stored in global space), all vars are ptrs and the store
    // instruction will thus be identical for non-ssa which makes things simple!
    std::string type_llvm = this->target->type->get_llvm();
    auto target_llvm = this->target->get_llvm();
    auto source_llvm = this->source->get_llvm();
    if(dynamic_pointer_cast<ast::InvocationExpression>(this->source)) {
        source_llvm = source_llvm.substr(1); // detab
        auto temp_reg = Register::create();
        llvm_ir += TAB+fmt::format("{} = {}\n",temp_reg->get_llvm(),source_llvm); 
        source_llvm = temp_reg->get_llvm();
    } else if(auto bin_exp = dynamic_pointer_cast<BinaryExpression>(this->source); bin_exp && bin_exp->is_i1()) {
        spdlog::debug("Zero extending binary expression!\n");
        llvm_ir += bin_exp->zext();
        source_llvm = this->source->get_llvm();
    }
    llvm_ir += TAB+fmt::format("store {} {}, ptr {}, align {}\n",type_llvm,source_llvm,target_llvm,this->target->type->alignment());
    spdlog::debug("assignment llvm = {}",llvm_ir);
	return llvm_ir;
}
 
void AssignmentStatement::typecheck(Env &env) {
    spdlog::debug("inside AssignmentStatement::{}\n",__func__);
    // Get the type of the lhs and rhs
    auto targetType = this->target->resolveType(env);
    auto sourceType = this->source->resolveType(env);
	const Type& targetRef = *targetType;
    const Type& sourceRef = *sourceType;
    const bool typesAreEqual = typeid(targetRef) == typeid(sourceRef);
    // Make sure the types are equal (unless it's null assignment to a struct)
    if(std::dynamic_pointer_cast<StructType >(targetType) && std::dynamic_pointer_cast<NullType >(sourceType)) {
        spdlog::debug("Found null assignment to struct");
    } else if(!typesAreEqual) {
        throw TypeException(fmt::format("target type {} != source type {}",*targetType,*sourceType));
    }
    spdlog::debug("line {}: target type {} ~ source type {}",this->getLineNum(),*targetType,*sourceType);
    spdlog::debug("equal? {}",typesAreEqual);
    // add the lhs to the env UPDATE: DONT THINK THIS IS NEEDED
    //env.addBinding(target->getId(),std::make_shared<Entry>(targetType));
}


}  // namespace ast
