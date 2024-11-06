#ifndef WHILESTATEMENT_HPP
#define WHILESTATEMENT_HPP

#include "AbstractStatement.hpp"
#include "Expression.hpp"
#include "Statement.hpp"
#include "Label.hpp"

namespace ast {

class WhileStatement : public AbstractStatement {
private:
    std::shared_ptr<Expression> guard;  // Pointer for polymorphic behavior
    std::shared_ptr<Statement> body;    // Pointer for polymorphic behavior
    std::shared_ptr<Label> label = nullptr;
    std::shared_ptr<Label> afterLabel = nullptr;

public:
    WhileStatement(int lineNum, std::shared_ptr<Expression> guard, std::shared_ptr<Statement> body);
	std::string display() const override {
		return fmt::format("WhileStatement(lineNum={})",lineNum);
	}
	void typecheck(Env &env, Function &f) override;
    std::vector<std::shared_ptr<Bblock>> get_cfg() override; 
    std::shared_ptr<Expression> get_guard() { return guard; }
    std::shared_ptr<Statement> get_body() { return body; }
    std::string get_llvm(Bblock &block) override;
};

} // namespace ast

#endif // WHILESTATEMENT_HPP

