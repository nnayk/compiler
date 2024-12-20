#ifndef ABSTRACT_STATEMENT_HPP
#define ABSTRACT_STATEMENT_HPP

#include "Statement.hpp"
#include "Env.hpp"
#include "Bblock.hpp"
//#include 
namespace ast {

class AbstractStatement : public Statement, public std::enable_shared_from_this<AbstractStatement> {
public:
    int lineNum;  // Equivalent to 'private final int' in Java
    // Constructor
    AbstractStatement(int lineNum);

    // Virtual destructor for proper cleanup of derived objects
    virtual ~AbstractStatement() {}
	
	int getLineNum() const override {
        return this->lineNum;
    }

    void setLineNum(int line) {
        this->lineNum = line;
    }
    virtual std::vector<std::shared_ptr<Bblock>> get_cfg() override;
    virtual std::string get_llvm(Bblock &block) override;
    virtual std::string get_ssa(Bblock &block) override;
    virtual void resolve_def_uses(Bblock &block) override;
    virtual std::string get_arm(Bblock &block) override;
    virtual bool guarantees_return(std::shared_ptr<Type> type) override;
};

}  // namespace ast

#endif  // ABSTRACT_STATEMENT_HPP
