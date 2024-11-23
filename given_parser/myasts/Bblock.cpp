#include "Bblock.hpp"
#include "ConditionalStatement.hpp"
#include "BlockStatement.hpp"
#include "AssignmentStatement.hpp"
#include "UseBeforeInitException.hpp"
#include "IdentifierExpression.hpp"

extern std::string TAB;
extern std::unordered_map<std::string,std::shared_ptr<Register>> all_regs;

Bblock::Bblock(): visited(0) {
    ssa_map = std::make_shared<Mapping>();
} 

std::string Bblock::get_llvm() {
    std::string llvm_ir;
    spdlog::debug("inside Bblock::{}",__func__);
    assert(label);
    spdlog::debug("bblock label = {}\n",label->getLabel());
    llvm_ir += "\n"+TAB+label->getLabel()+":\n";  
    for(auto stmt:this->stmts) {
        spdlog::debug("Invoking get_llvm() for {}\n",*stmt);
        llvm_ir += stmt->get_llvm(*this);
        spdlog::debug("Finished get_llvm() for {}\n",*stmt);
    }
    spdlog::debug("finished llvm gen for nested stmts for bblock label = {}\n",label->getLabel());
    // The 2nd condition is necessary as the AssignmentStatement::get_llvm() for _ret would've already
    // added the br to the final return bblock
    if(this->children.size()==1 && !this->children[0]->final_return_block) { 
        spdlog::debug("adding extra br\n");
        auto br_llvm = TAB+fmt::format("br label %{}",this->children[0]->label->getLabel());
        spdlog::debug("br_llvm = {}\n",br_llvm);
        llvm_ir += br_llvm; 
    }
    /*
    if(this->is_return_block()) {
        spdlog::debug("adding extra br for return block:{}\n",*this);
        llvm_ir += TAB+"br label %Lreturn\n";
    }
    */
    return llvm_ir+"\n";
}

std::string Bblock::get_ssa() {
    std::string ssa = "";
    spdlog::debug("inside Bblock::{}",__func__);
    assert(label);
    spdlog::debug("bblock label = {}\n",label->getLabel());
    ssa += "\n"+TAB+label->getLabel()+":\n"; 
    spdlog::debug("Gonna add ssa for the {} phis\n",this->phis.size());
    for(auto phi : this->phis) {
        ssa += phi->get_ssa();
    }
    for(auto stmt:this->stmts) {
        spdlog::debug("Invoking get_ssa() for {}\n",*stmt);
        ssa += stmt->get_ssa(*this);
        spdlog::debug("Finished get_ssa() for {}\n",*stmt);
    }
    spdlog::debug("finished ssa gen for nested stmts for bblock label = {}\n",label->getLabel());
    // The 2nd condition is necessary as the AssignmentStatement::get_ssa() for _ret would've already
    // added the br to the final return bblock
    if(this->children.size()==1 && !this->children[0]->final_return_block) { 
        spdlog::debug("adding extra br\n");
        auto br_ssa = TAB+fmt::format("br label %{}",this->children[0]->label->getLabel());
        spdlog::debug("br_ssa = {}\n",br_ssa);
        ssa += br_ssa; 
    }
    return ssa+"\n";
}

std::string Bblock::display() const {
        spdlog::debug("inside Bblock::{}\n",__func__);
        std::string out = "";
        if(this->label) {
            spdlog::debug("label exists: {}\n",this->label->getLabel());
            out += fmt::format("Label {}\n",this->label->getLabel());
        } else {
            spdlog::debug("Label dne yet!\n");
        }
        out += fmt::format("Head statement: ");
        if(this->stmts.size() > 0) {
            out += fmt::format("# of stmts = {}\n",this->stmts.size());
            out += fmt::format("{}",*this->stmts[0]);
        }else {
            out += fmt::format("Null stmt, dummy block");
        }
        out += fmt::format("STATEMENTS:\n");
		for(auto stmt : this->stmts) {
			out += fmt::format("{}\n",*stmt);//->display());
		}
		out += fmt::format("\nNUMBER OF CHILDREN: {}\n", this->children.size());
		out += fmt::format("CHILDREN:\n");
		for(auto child : this->children) {
            if(child->stmts.size() > 0) {
                out += fmt::format("Child # stmts={}\n",child->stmts.size());
                out += fmt::format("HEAD STMT: {}\n",*(child->stmts[0]));
            } else {
                out += fmt::format("DUMMY CHILD with {} children, {} parents",child->children.size(),child->parents.size());
            }
		}
		out += fmt::format("\nNUMBER OF PARENTS: {}\n", this->parents.size());
		out += fmt::format("PARENTS:\n");
		for(auto parent : this->parents) {
            if(parent->stmts.size() > 0) {
                out += fmt::format("Parent # stmts={}\n",parent->stmts.size());
                out += fmt::format("HEAD STMT: {}\n",*(parent->stmts[0]));
            }else
                out += fmt::format("DUMMY parent\n");
		}
		return out;
}

std::shared_ptr<Register> Bblock::lookup(std::shared_ptr<ast::IdentifierExpression> id_expr) {
    spdlog::debug("inside Bblock::{}\n",__func__);
    auto id = id_expr->getId();
    spdlog::debug("Looking up register for id {}\n",id);
    if(auto reg = this->ssa_map->entries[id]) {
        spdlog::debug("Resolved var {} to register {}\n",id,*reg);
        return reg;
    } else {
        spdlog::debug("Didn't find id in current block, looking at preds\n");
        auto parents = this->parents;
        if(parents.size()==0) {
            assert(this->label->getLabel()=="L0");
            throw UseBeforeInitException(fmt::format("Uninitialized var {}\n",id));
        } else if(parents.size()==1) {
            spdlog::debug("Only 1 pred, yay!\n");
            this->ssa_map->entries[id] = parents[0]->lookup(id_expr);
            return this->ssa_map->entries[id];
        } else {
            spdlog::debug("Multiple preds, gotta create a phi instruction!\n");
            //TODO: Implement. Consider sealed vs unsealed blocks
            auto phi = std::make_shared<Phi>();
            for(auto parent : this->parents) {
                if(this->is_loopback_parent(parent)) {
                    spdlog::debug("skipping loopback parent {}\n",*parent);
                    this->sealed = false;
                } else {
                    auto parent_reg = parent->lookup(id_expr);
                    assert(parent_reg);
                    auto parent_label = parent->label->getLabel();
                    assert(parent_label != "");
                    spdlog::debug("parent {} resolved var {} to parent_register {}\n",parent_label,id,*parent_reg);
                    // create the phi pair and add it to the phi object
                    phi->addEntry(parent_label,parent_reg);
                }
            }
            auto assignee = Register::create();
            // assign a register to the phi instruction and return it (also make sure to set phi assignee attr to the register AND also set phi block attr accordingly)
            phi->assignee = assignee;
            phi->type = id_expr->type;
            phi->block = shared_from_this();
            spdlog::debug("Created phi for id {} with assignee {}:\n",id,*assignee);
            spdlog::debug("{}\n",*phi);
            this->ssa_map->addEntry(id,assignee);
            this->phis.push_back(phi);
            return assignee;
        }
    }
}

bool Bblock::is_loopback_parent(std::shared_ptr<Bblock> target) {
    spdlog::debug("inside Bblock::{}\n",__func__);
    auto source = this->loopback_parents;
    bool found =  std::find(source.begin(),source.end(),target) != source.end();
    spdlog::debug("is a loopback parent? {}\n",found);
    return found;
}

void Bblock::add_phis(std::vector<ast::Declaration> locals,std::vector<ast::Declaration> params) {
    spdlog::debug("inside Bblock::add_phis\n");
    assert(this->parents.size()>1);
    //std::shared_ptr<Register> parent_reg = nullptr;
    std::shared_ptr<Register> reg = nullptr;
    // not needed for L0 (in fact we'll get UndefinedUsage Error)
    // Loop over each local var
    for(auto local : locals) {
        // create a new phi object
        for(auto parent : this->parents) {
            if(this->is_loopback_parent(parent)) {
                spdlog::debug("skipping loopback parent {}\n",*parent);
                this->sealed = false;
            } else {
                // TODO: implement Bblock::lookup
                //reg = parent->lookup(local);
                assert(reg);
                this->ssa_map->addEntry(local.getName(),reg);
                // create the phi pair and add it to the phi object
            }
        }
    }
    // TODO: do the same as above but for params (rn will not test w/params but need to support this...)
}

void Bblock::add_initial_mapping(std::vector<ast::Declaration> params) {
    assert(this->parents.size()==0);
    assert(this->label->getLabel()=="L0");
    spdlog::debug("inside Bblock::{}\n",__func__);
    for(auto param: params) {
        auto name = param.getName(); 
        assert(all_regs.find(name) == all_regs.end());
        auto reg = Register::create(name);
        this->ssa_map->addEntry(name,reg);
    }
}

void Bblock::resolve_def_uses() {
    spdlog::debug("inside Bblock::{}\n",__func__);
    for(auto stmt : this->stmts) {
        spdlog::debug("resolving def/uses for stmt {}\n",*stmt); 
        stmt->resolve_def_uses(*this);
    }
    spdlog::debug("done resolving def uses\n");
}

std::string Bblock::get_arm() {
    spdlog::debug("inside BBlock::{}\n",__func__);
    std::string arm = "";
    for(auto stmt : this->stmts) {
        arm += stmt->get_arm(*this);
    }
    return arm;
}

