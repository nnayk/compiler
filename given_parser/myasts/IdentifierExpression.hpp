#ifndef IDENTIFIER_EXPRESSION_HPP
#define IDENTIFIER_EXPRESSION_HPP

#include <string>
#include "AbstractExpression.hpp"
#include "Register.hpp"
#include "CfgFunc.hpp"

namespace ast {

class IdentifierExpression : public AbstractExpression {
public:
    int scope = 0;
    // Constructor
    IdentifierExpression(int lineNum, const std::string& id);

    // Getter for the identifier
    const std::string& getId() const;
    std::shared_ptr<Type> resolveType(Env &env) override;
    std::string display() const override {
        return fmt::format("IdentifierExpression(lineNum={},id={})\n",lineNum,this->getId());
    }
    std::string get_llvm_init(Bblock &block) override; 
    std::string get_llvm(Bblock &block) override; 
    std::string get_ssa(Bblock &block);

private:
    std::string id;  // Identifier string
protected:
};

} // namespace ast

#endif // IDENTIFIER_EXPRESSION_HPP

