#ifndef INTEGER_EXPRESSION_HPP
#define INTEGER_EXPRESSION_HPP

#include "AbstractExpression.hpp"
#include <string>

namespace ast {

class IntegerExpression : public AbstractExpression {
public:
    // Constructor
    IntegerExpression(int lineNum, const std::string& value);

    // Getter for the value
    std::string getValue() const;
    std::shared_ptr<Type> resolveType(Env &env) override;
    std::string display() const override {
        return fmt::format("IntegerExpression(lineNum={},value={})\n",lineNum,this->getValue());
    }
    std::string get_llvm(Bblock &block) override; 
    virtual std::string get_ssa(Bblock &block) override;
    virtual std::string get_arm(Bblock &block) override;
    void resolve_uses(Bblock &block) override;
private:
    std::string value; // The integer value as a string
};

} // namespace ast

#endif // INTEGER_EXPRESSION_HPP

