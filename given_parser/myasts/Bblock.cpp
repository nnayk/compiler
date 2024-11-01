#include "Bblock.hpp"
#include "ConditionalStatement.hpp"
#include "BlockStatement.hpp"

extern std::string TAB;
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
        llvm_ir += stmt->get_llvm();
    }
    if(is_cond_block()) {
        spdlog::debug("dealing with cond  block...\n");
        assert(!this->jmp_label);
        auto cond_stmt = dynamic_pointer_cast<ast::ConditionalStatement>(this->stmts[this->stmts.size()-1]);
        // Get the after block and assign it the after label chosen by the cond stmt
        std::shared_ptr<Bblock> after_block = nullptr;
        auto thenBblock = dynamic_pointer_cast<Bblock>(this->children[0]);
        assert(thenBblock);
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
            // Not true for while block as it also has a self loop
            //assert(thenBblock->children.size()==1);
            thenBblock->children[0]->label = cond_stmt->afterLabel;
        }
    } else if(!is_while_block() && this->jmp_label) {
        llvm_ir += TAB+fmt::format("br label %{}\n",jmp_label->getLabel());
    }
    return llvm_ir+"\n";
}

bool Bblock::is_while_block() {
    // If there's a self loop it must be a while block
   for(auto child : this->children) {
       if(child.get()==this) return true;
   }
   return false;
}

bool Bblock::is_cond_block() {
    if(this->is_while_block()) return false;
    if(this->stmts.size() && dynamic_pointer_cast<ast::ConditionalStatement>(this->stmts[this->stmts.size()-1])) return true;
    return false;
}
