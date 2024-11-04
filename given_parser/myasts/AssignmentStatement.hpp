#ifndef ASSIGNMENT_STATEMENT_HPP
#define ASSIGNMENT_STATEMENT_HPP

#include "AbstractStatement.hpp"
#include "Lvalue.hpp"
#include "Expression.hpp"
#include <memory>
#include <spdlog/spdlog.h>
#include "Bblock.hpp"
#include "CfgFunc.hpp"

namespace ast {

class AssignmentStatement : public AbstractStatement {
private:
    std::shared_ptr<Lvalue> target;   // Pointer for target to manage memory
    std::shared_ptr<Expression> source; // Pointer for source to manage memory

public:
    // Constructor
    AssignmentStatement(int lineNum, std::shared_ptr<Lvalue> target, std::shared_ptr<Expression> source);
    virtual void typecheck(Env &env, Function &f) override;

    // Getter for target
    std::shared_ptr<Lvalue> getTarget() const;

    // Getter for source
    std::shared_ptr<Expression> getSource() const;
    
	virtual std::string get_llvm() override;

    std::string get_ssa(CfgFunc &f);

    std::string display() const override {
        return fmt::format("AssignmentStatement(lineNum={})",lineNum);
    }
};

}  // namespace ast

#endif  // ASSIGNMENT_STATEMENT_HPP
