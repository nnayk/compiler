
    int index = 0;
    int num_stmts = this->statements.size();
    std::shared_ptr<Bblock> single_block;
    std::vector<std::shared_ptr<Bblock>> new_blocks;
    std::vector<std::shared_ptr<Bblock>> prev_blocks;
    std::vector<std::shared_ptr<Bblock>> blocks;
    while(index < num_stmts) {
        single_block = nullptr;
        for(int j=index;j<num_stmts;j++) {
            auto curr_stmt = this->statements[j];
            curr_blocks = curr_stmt->get_cfg(); 
            if((auto cond_stmt = dynamic_pointer_cast<ast::ConditionalStatement>(curr_stmt))) {
                
            } else if((auto while_stmt = dynamic_pointer_cast<ast::WhileStatement>(curr_stmt))) {
            
            } else {
                assert(curr_block.size()==1);
                if(!single_block) single_block = curr_blocks[0];
                single_block->stmts.push_back(curr_stmt);
            }
            index++;
        }
    }
