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
    if(label) 
    {
        spdlog::debug("bblock label = {}\n",label->getLabel());
        llvm_ir += "\n"+TAB+label->getLabel()+":\n";  
    }

    if(jmp_label) spdlog::debug("jmp label = {}\n",jmp_label->getLabel());
    else spdlog::debug("null jump label\n");
    // the while processing must be done b4 processing the stmts b/c the thenLabel and afterLabel need to be set b4 getting the llvm for the while conditional stmt. For the cond stmt after the for loop processing it later is ok since it just decides the labels for its children.
    // 11/8/24: SAFE TO DELETE I BELIEVE!!!
    if(is_while_block()) {
        spdlog::debug("dealing with while block...\n");
        assert(this->jmp_label); // parent cond should've set this
        auto cond_stmt = dynamic_pointer_cast<ast::ConditionalStatement>(this->stmts[this->stmts.size()-1]);
        assert(cond_stmt);
        assert(!cond_stmt->elseBlock); // all while conditionals should have a null elseBlock
        cond_stmt->thenLabel = this->label;
        cond_stmt->afterLabel = this->jmp_label;
    }
    for(auto stmt:this->stmts) {
        spdlog::debug("Invoking get_llvm() for {}\n",*stmt);
        llvm_ir += stmt->get_llvm(*this);
    }
    if(this->is_return_block()) {
        spdlog::debug("adding extra br for return block:{}\n",*this);
        llvm_ir += TAB+"br label %Lreturn\n";
    }
    // 11/8/24: SAFE TO DELETE I BELIEVE!!! HOWEVER NEED TO ADD SOME CHECKS TO ADD a br to child label if applicable!!
    if(is_cond_block()) {
        spdlog::debug("dealing with cond  block...\n");
        auto cond_stmt = dynamic_pointer_cast<ast::ConditionalStatement>(this->stmts[this->stmts.size()-1]);
        spdlog::debug("cond_stmt = {}\n",*this->stmts[this->stmts.size()-1]);
        //assert(!this->jmp_label);
        // Get the after block and assign it the after label chosen by the cond stmt
        std::shared_ptr<Bblock> after_block = nullptr;
        auto thenBblock = dynamic_pointer_cast<Bblock>(this->children[0]);
        assert(thenBblock);
        // Nov 3 2024: handle cases where then and/or else block is also a conditional... in this case we need to update their afterLabels
        if(cond_stmt->thenLabel != cond_stmt->afterLabel) {
            thenBblock->label = cond_stmt->thenLabel;
            thenBblock->jmp_label = cond_stmt->afterLabel;
        } else {
            spdlog::debug("then bblock is after bblock\n");
            thenBblock->label = cond_stmt->afterLabel;
            thenBblock->jmp_label = nullptr;
        }
        auto elseBblock = dynamic_pointer_cast<Bblock>(this->children[1]);
        assert(elseBblock);
        if(cond_stmt->elseLabel != cond_stmt->afterLabel) {
            elseBblock->label = cond_stmt->elseLabel;
            elseBblock->jmp_label = cond_stmt->afterLabel;
        } else {
            spdlog::debug("else bblock is after bblock\n");
            elseBblock->label = cond_stmt->afterLabel;
            elseBblock->jmp_label = nullptr;
        }

        // Assign label to after block if not done yet (i.e. then and else are both noth equal to after block) 
        if((cond_stmt->thenLabel != cond_stmt->afterLabel ) && (cond_stmt->elseLabel != cond_stmt->afterLabel)) {
            // Not true for while block as it also has a self loop -- URGENT: also not true for nested ifs as then block would have 2 children then. FIX THIS SO WE ITERATE OVER EACH CHILDREN, SKIPPING THE CHILD IF IT'S EQUAL TO THE THEN BLOCK. ALSO MAY NEED TO ITERATE OVER THE ELSE BLOCK AS WELL
            //assert(thenBblock->children.size()==1);
            thenBblock->children[0]->label = cond_stmt->afterLabel;
        }
    } else if(!is_while_block() && this->jmp_label) {
        llvm_ir += TAB+fmt::format("br label %{}\n",jmp_label->getLabel());
    }
    return llvm_ir+"\n";
}

bool Bblock::is_return_block() {
    spdlog::debug("inside Bblock::{}\n",__func__);
    if(auto size = this->stmts.size()) {
        auto asgn_stmt = dynamic_pointer_cast<ast::AssignmentStatement>(this->stmts[size-1]);
        if(asgn_stmt && asgn_stmt->getTarget()->getId() == "_ret") {
            spdlog::debug("yes, it's a return block:{}\n",*this);
            if(this->children.size()==1) {
                return true;
            assert(this->children.size()==0); // got THE return block
            }
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
