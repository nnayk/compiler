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

std::string AssignmentStatement::get_llvm() {
	spdlog::debug("inside AssignmentStatement:{}\n",__func__);
	std::string llvm_ir = "AssignmentStatement\n";
	//TODO: impleement get_llvm for expr + lvalue classes
	//std::string target_llvm = this->target->get_llvm();
	//std::string source_llvm = this->source->get_llvm();
	//llvm_ir += target_llvm;
	//llvm_ir += source_llvm;
	// Add llvm ir to perform the assignment
	
	return llvm_ir;
}
 
void AssignmentStatement::typecheck(Env &env) {
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
