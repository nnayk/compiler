#include "AssignmentStatement.hpp"
#include "Types.hpp"
#include "InvocationExpression.hpp"
#include "BinaryExpression.hpp"
#include "IdentifierExpression.hpp"
#include "DotExpression.hpp"
#include "Mapping.hpp"

extern std::string TAB;
extern std::unordered_map<std::string,std::shared_ptr<Register>> all_regs;

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
std::string AssignmentStatement::get_llvm(Bblock &block) {
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
	std::string target_llvm_init = this->target->get_llvm_init(block);
    spdlog::debug("Got target llvm for id {}: {}\n",this->target->getId(),target_llvm_init);
    spdlog::debug("Target id = {}, type = {}\n",this->target->getId(), *this->target->type);
    std::string source_llvm_init = this->source->get_llvm_init(block);
    spdlog::debug("Got source llvm: {}\n",source_llvm_init);
	llvm_ir += target_llvm_init;
	llvm_ir += source_llvm_init;
	//Add llvm ir to perform the assignment
	//Note: Since I'm allocating all local vars on the stack (and global vars+
    // structs are stored in global space), all vars are ptrs and the store
    // instruction will thus be identical for non-ssa which makes things simple!
    std::string type_llvm = this->target->type->get_llvm();
    auto target_llvm = this->target->get_llvm(block);
    auto source_llvm = this->source->get_llvm(block);
    if(dynamic_pointer_cast<ast::InvocationExpression>(this->source)) {
        source_llvm = source_llvm.substr(1); // detab
        auto temp_reg = Register::create();
        llvm_ir += TAB+fmt::format("{} = {}\n",temp_reg->get_llvm(),source_llvm); 
        source_llvm = temp_reg->get_llvm();
    } else if(auto bin_exp = dynamic_pointer_cast<BinaryExpression>(this->source); bin_exp && bin_exp->is_i1()) {
        spdlog::debug("Zero extending binary expression!\n");
        llvm_ir += bin_exp->zext();
        source_llvm = this->source->get_llvm(block);
    }
    llvm_ir += TAB+fmt::format("store {} {}, ptr {}, align {}\n",type_llvm,source_llvm,target_llvm,this->target->type->alignment());
    spdlog::debug("assignment llvm = {}",llvm_ir);
    //special case return stmt
    if(this->target->getId() == "_ret") {
        for(auto child : block.children) {
            if(child->final_return_block) {
                spdlog::debug("found final return block child, gonnabreak to it\n");
                auto return_label = child->label->getLabel();
                spdlog::debug("return label = {}\n",return_label);
                llvm_ir += TAB+fmt::format("br label %{}\n",return_label);
            }
        }
    }
	return llvm_ir;
}

std::string AssignmentStatement::get_ssa(Bblock &block) {
    spdlog::debug("inside AssignmentStatement::{}\n",__func__);
    spdlog::debug("lineNum = {}\n",this->getLineNum());
    std::string ssa = "";
    spdlog::debug("source = {}\n",*(this->source));
    assert(this->source);
    assert(this->target);
    assert(this->target->type);
    assert(this->source->type);
    // TODO:
    // 1. if target is a struct then just generate non-ssa llvm
    // otherwise if target is not a struct generate ssa
    // temporary llvm won't change
    // 2. if source is a global (lvalueId should contain a scope field and mark it based on resolveType just like IdExpr does) then generate non-ssa
    ssa += this->source->get_llvm_init(block);
    std::shared_ptr<Register> reg;
    const std::type_info& source_type = typeid(this->source->type);
    // if source is an immediate create a pseudo reg
    if((source_type == typeid(IntType)) || (source_type == typeid(BoolType))) {
        // Can get the llvm for immediates (technically it's not non-ssa specific since we're dealing with simple constants...it's just poor nomenclature for the functions which made sense at the time when I was focused on non-ssa)
        auto val = this->source->get_llvm(block);
        reg = Register::create(val,false,true);
        //reg->content_type = 
    // else create a non-pseudo reg
    } else {
        // if source isn't a binary expression then we need to create the lvalue register and add the llvm 
        if(dynamic_pointer_cast<BinaryExpression>(this->source)) {
            reg = this->source->getResult();
        } else {
            reg = Register::create();
            ssa += fmt::format("{} = {}",reg->get_llvm(),this->source->get_llvm(block));
        }
    }
    // add the var mapping to the function map
    // Since structs have already been handled we know we're dealing with an identifier at this point
    auto id_expr = dynamic_pointer_cast<IdentifierExpression>(this->target);
    assert(id_expr);
    //f.ssa_map->addEntry(id_expr->getId(),reg); 
    return ssa;
}
 
void AssignmentStatement::typecheck(Env &env, Function &f) {
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

void AssignmentStatement::resolve_def_uses(Bblock &block) {
    spdlog::debug("inside AssignmentStatement::{}\n",__func__);
    // Crucial that usages are resolved first b/c it's possible that the user
    // attempts to do smth like x=x+1 where x has not been defined yet...resolving
    // usages would catch this undefined usage error
    this->source->resolve_uses();
    this->target->resolve_def();
    std::string var = "";
    if(auto dot_expr = dynamic_pointer_cast<DotExpression>(this->target)) {
        var = dot_expr->get_topmost_id();
    } else {
        var = this->target->getId();
    }
    block.ssa_map->addEntry(var,this->target->getResult());
}


}  // namespace ast
