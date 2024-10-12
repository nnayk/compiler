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

void AssignmentStatement::typecheck(Env &env) {
    // Get the type of the lhs and rhs
    auto targetType = this->target->resolveType();
    auto sourceType = this->source->resolveType();
    // Make sure the types are equal (unless it's null assignment to a struct)
    if(std::dynamic_pointer_cast<StructType >(targetType) && std::dynamic_pointer_cast<NullType >(sourceType)) {
        spdlog::debug("Found null assignment to struct");
    } else if(typeid(targetType) != typeid(sourceType)) {
        spdlog::debug("target type {} != source type {}",*targetType,*sourceType);
    }
    // add the lhs to the env
    env.addBinding(target->getId(),std::make_shared<Entry>(targetType));
}


}  // namespace ast
