#include "Bblock.hpp"
#include "ConditionalStatement.hpp"
#include "BlockStatement.hpp"
#include "AssignmentStatement.hpp"

extern std::string TAB;

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
    if(this->children.size()==1 && !this->children[0]->final_return_block) {
        spdlog::debug("adding extra br\n");
        llvm_ir += TAB+fmt::format("br label %{}",this->children[0]->label->getLabel());
    }
    /*
    if(this->is_return_block()) {
        spdlog::debug("adding extra br for return block:{}\n",*this);
        llvm_ir += TAB+"br label %Lreturn\n";
    }
    */
    return llvm_ir+"\n";
}

bool Bblock::is_return_block() {
    spdlog::debug("inside Bblock::{}\n",__func__);
    if(auto size = this->stmts.size()) {
        auto asgn_stmt = dynamic_pointer_cast<ast::AssignmentStatement>(this->stmts[size-1]);
        if(asgn_stmt && asgn_stmt->getTarget()->getId() == "_ret") {
            spdlog::debug("yes, it's a return block:{}\n",*this);
            assert(this->children.size()==1 || this->children.size()==2); 
            return true;
        }
    }
    return false;
}

bool Bblock::is_while_block() {
    spdlog::debug("inside Bblock::{}\n",__func__);
    // If there's a self loop it must be a while block
   for(auto child : this->children) {
       if(child.get()==this) return true;
   }
   return false;
}

bool Bblock::is_cond_block() {
    spdlog::debug("inside Bblock::{}\n",__func__);
    if(this->is_while_block()) return false;
    if(this->stmts.size() && dynamic_pointer_cast<ast::ConditionalStatement>(this->stmts[this->stmts.size()-1])) return true;
    return false;
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

std::shared_ptr<Register> Bblock::lookup(std::string id) {
    spdlog::debug("inside Bblock::{}\n",__func__);
    spdlog::debug("Looking up register for id {}\n",id);
    std::shared_ptr<Register> reg = nullptr;
    if((reg = this->ssa_map->entries[id])) {
        spdlog::debug("Found register {}, pseudo = {}\n",*reg,reg->pseudo);
        return reg;
    } else {
        spdlog::debug("Didn't find id in current block, looking at preds\n");
        auto parents = this->parents;
        if(parents.size()==1) {
            spdlog::debug("Only 1 pred, yay!\n");
            this->ssa_map->entries[id] = parents[0]->lookup(id);
            return this->ssa_map->entries[id];
        }
        spdlog::debug("Multiple preds, gotta create a phi instruction!\n");
        //TODO: Implement
        /*
        for(auto parent : this->parents) {
        }
        */
    }
    return reg;
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

void Bblock::resolve_def_uses() {
    spdlog::debug("inside Bblock::{}\n",__func__);
}
