#ifndef WHILESTATEMENT_HPP
#define WHILESTATEMENT_HPP

#include "AbstractStatement.hpp"
#include "Expression.hpp"
#include "Statement.hpp"

namespace ast {

class WhileStatement : public AbstractStatement {
private:
    std::shared_ptr<Expression> guard;  // Pointer for polymorphic behavior
    std::shared_ptr<Statement> body;    // Pointer for polymorphic behavior

public:
    WhileStatement(int lineNum, std::shared_ptr<Expression> guard, std::shared_ptr<Statement> body);
	std::string display() const override {
		return fmt::format("WhileStatement(lineNum={})",lineNum);
	}
};

} // namespace ast

#endif // WHILESTATEMENT_HPP

