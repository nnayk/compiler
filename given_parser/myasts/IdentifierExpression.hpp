#ifndef IDENTIFIER_EXPRESSION_HPP
#define IDENTIFIER_EXPRESSION_HPP

#include <string>
#include "AbstractExpression.hpp"
#include "Register.hpp"

namespace ast {

class IdentifierExpression : public AbstractExpression {
public:
     std::shared_ptr<ast::Type> type = nullptr; 
    // Constructor
    IdentifierExpression(int lineNum, const std::string& id);

    // Getter for the identifier
    const std::string& getId() const;
    std::shared_ptr<Type> resolveType(Env &env) override;
    std::string display() const override {
        return fmt::format("IdentifierExpression(lineNum={},id={})\n",lineNum,this->getId());
    }
    std::string get_llvm_init() override; 
    std::string get_llvm() override; 

private:
    std::string id;  // Identifier string
protected:
    std::shared_ptr<Register> deref_result=nullptr; // see similar comment about similar attr in Lvalue.hpp for explanation
};

} // namespace ast

#endif // IDENTIFIER_EXPRESSION_HPP

