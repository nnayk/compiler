#include "AssignmentStatement.hpp"
#include "Types.hpp"
#include "InvocationExpression.hpp"
#include "BinaryExpression.hpp"
#include "IdentifierExpression.hpp"
#include "DotExpression.hpp"
#include "Mapping.hpp"
#include "utils.hpp"
#include "LvalueId.hpp"

extern std::string TAB;
extern std::unordered_map<std::string,std::shared_ptr<Register>> all_regs;
extern bool use_ssa;

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
    // TODO: P sure this case is messed up since InvocExpr already performs an ssignment... see the note at InvocExpr::get_llvm abt seg fault
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

// Returns the SSA string of instructions for the assignment
std::string AssignmentStatement::get_ssa(Bblock &block) {
	spdlog::debug("inside AssignmentStatement:{}\n",__func__);
    spdlog::debug("lineNum = {}\n",this->getLineNum());
	std::string ssa = "";
    spdlog::debug("source = {}\n",*(this->source));
    assert(this->source);
    assert(this->target);
    assert(this->target->type);
    assert(this->source->type);
	std::string target_ssa_init = this->target->get_ssa_init(block);
    spdlog::debug("Got target ssa for id {}: {}\n",this->target->getId(),target_ssa_init);
    spdlog::debug("Target id = {}, type = {}\n",this->target->getId(), *this->target->type);
    std::string source_ssa_init = this->source->get_ssa_init(block);
    spdlog::debug("Got source ssa: {}\n",source_ssa_init);
	ssa += target_ssa_init;
	ssa += source_ssa_init;

	//Add ssa ir to perform the assignment
    std::string type_ssa = this->target->type->get_llvm(); // TODO P3: create get_ssa for all type classes
    auto source_ssa = this->source->get_ssa(block);
    auto target_ssa = this->target->get_ssa(block);
    // TODO: Add check for invocation (+ global) -- here we'd need a store instruction
    if(auto bin_exp = dynamic_pointer_cast<BinaryExpression>(this->source); bin_exp && bin_exp->is_i1()) {
        spdlog::debug("Zero extending binary expression!\n");
        ssa += bin_exp->zext();
        this->target->setResult(bin_exp->getResult());
    }
    spdlog::debug("assignment ssa = {}",ssa);
    //special case return stmt
    if(this->target->getId() == "_ret") {
        for(auto child : block.children) {
            if(child->final_return_block) {
                spdlog::debug("found final return block child, gonnabreak to it\n");
                auto return_label = child->label->getLabel();
                spdlog::debug("return label = {}\n",return_label);
                ssa += TAB+fmt::format("br label %{}\n",return_label);
            }
        }
    }
	return ssa;
}

std::string AssignmentStatement::get_arm(Bblock &block) {
    spdlog::debug("inside AssignmentStatement::{}\n",__func__);
    spdlog::debug("lineNum = {}\n",this->getLineNum());
	std::string arm = "";
    spdlog::debug("source = {}\n",*(this->source));
    assert(this->source);
    assert(this->target);
    assert(this->target->type);
    assert(this->source->type);
	std::string target_arm_init = this->target->get_arm_init(block);
    spdlog::debug("Got target arm for id {}: {}\n",this->target->getId(),target_arm_init);
    spdlog::debug("Target id = {}, type = {}\n",this->target->getId(), *this->target->type);
    std::string source_arm_init = this->source->get_arm_init(block);
    spdlog::debug("Got source arm: {}\n",source_arm_init);
	arm += target_arm_init;
	arm += source_arm_init;
    std::string type_arm = this->target->type->get_llvm(); // TODO P3: create get_arm for all type classes
    // think this only works for LvalueId assignment
    int offset = (*block.stack_offsets)[this->target->getId()];
    arm += TAB+fmt::format("str {}, [sp, {}]\n",this->source->get_arm(block),(offset+2)*8);
    // TODO: consider struct assignment
    // TODO: Add check for invocation (+ global) -- here we'd need a store instruction
    // TODO: Look into this if stmt + special case return stmt below
    if(auto bin_exp = dynamic_pointer_cast<BinaryExpression>(this->source); bin_exp && bin_exp->is_i1()) {
        spdlog::debug("Zero extending binary expression!\n");
        // TODO: create an arm zext (ie.. just ANDs w/#1)
        arm += bin_exp->zext();
        this->target->setResult(bin_exp->getResult());
    }
    spdlog::debug("assignment arm = {}",arm);
    //special case return stmt
    if(this->target->getId() == "_ret") {
        for(auto child : block.children) {
            if(child->final_return_block) {
                spdlog::debug("found final return block child, gonnabreak to it\n");
                auto return_label = child->label->getLabel();
                spdlog::debug("return label = {}\n",return_label);
                arm += TAB+fmt::format("b {}\n",return_label);
            }
        }
    } 
    return arm;
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
    this->source->resolve_uses(block);
    auto source_result = this->source->getResult();
    assert(source_result);
    spdlog::debug("source result reg = {}\n",*source_result);
    // LvalueIds can just reuse the source's result register
    if(dynamic_pointer_cast<LvalueId>(this->target)) {
        spdlog::debug("LvalueId {}, reusing source result {}\n",this->target->getId(),*source_result);
        this->target->setResult(source_result);
        spdlog::debug("adding ssa_map entry for {}\n",this->target->getId());
        block.ssa_map->addEntry(this->target->getId(),source_result);
    } else {
        spdlog::debug("Target is an LvalueDot (id = {}), skipping for now!",this->target->getId());
    }
    /*
    auto source_type = this->source->type;
    std::string source_immediate = "";
    // if source is an immediate create a pseudo reg
    if(is_immediate(this->source)) {
        spdlog::debug("source {} is an immediate\n",*source);
        source_immediate = this->source->get_llvm(block);
        spdlog::debug("source = {}\n",source_immediate);
    } else {
        spdlog::debug("source {} is NOT an immediate\n",*source);
    }
    this->target->resolve_def(source_immediate);
    std::string var = "";
    if(auto dot_expr = dynamic_pointer_cast<DotExpression>(this->target)) {
        var = dot_expr->get_topmost_id();
    } else {
        var = this->target->getId();
    }*/
    // if dealing with an LvalueId then update the mapping. For LvalueDots doesn't make sense
    // since we only want mappings from the top level id to the RHS result register
    /*
    if() {
    }
    block.ssa_map->addEntry(var,this->target->getResult());
    */
}

}  // namespace ast
