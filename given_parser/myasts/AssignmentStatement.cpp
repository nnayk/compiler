#include "AssignmentStatement.hpp"
#include "Types.hpp"

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
	std::string llvm_ir = "AssignmentStatement\n";
	//TODO: impleement get_llvm_init for expr + lvalue classes
	std::string target_llvm_init = this->target->get_llvm_init();
    spdlog::debug("Got target llvm\n");
	std::string source_llvm_init = this->source->get_llvm_init();
    spdlog::debug("Got source llvm\n");
	llvm_ir += target_llvm_init;
	llvm_ir += source_llvm_init;
	//Add llvm ir to perform the assignment
	//Note: Since I'm allocating all local vars on the stack (and global vars+
    // structs are stored in global space), all vars are ptrs and the store
    // instruction will thus be identical for non-ssa which makes things simple!
    std::string type_llvm = this->target->type->get_llvm();
    llvm_ir += fmt::format("store {} {}, ptr %{}, align {}\n",type_llvm,this->source->get_llvm(),this->target->get_llvm(),this->target->type->alignment());
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
        spdlog::debug("target type {} != source type {}",*targetType,*sourceType);
    }
    spdlog::debug("line {}: target type {} ~ source type {}",this->getLineNum(),*targetType,*sourceType);
    spdlog::debug("equal? {}",typesAreEqual);
    // add the lhs to the env
    env.addBinding(target->getId(),std::make_shared<Entry>(targetType));
}


}  // namespace ast
