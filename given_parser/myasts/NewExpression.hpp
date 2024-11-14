#ifndef NEW_EXPRESSION_HPP
#define NEW_EXPRESSION_HPP

#include "AbstractExpression.hpp"
#include <string>
#include "Register.hpp"

namespace ast {

class NewExpression : public AbstractExpression {
public:
    int struct_size = 0;
    // Constructor
    NewExpression(int lineNum, const std::string& id);

    // Getter method for id
    const std::string& getId() const;
    std::string display() const override {
        auto output = fmt::format("NewExpression(lineNum={},struct={})",lineNum,id);
        output+="\n";
        return output;
    }
    std::string get_llvm_init(Bblock &block) override; 
    std::string get_llvm(Bblock &block) override; 
    virtual std::string get_ssa_init(Bblock &block) override;
    virtual std::string get_ssa(Bblock &block) override;
    std::shared_ptr<Type> resolveType(Env &env) override;
    void resolve_uses(Bblock &block) override;

private:
    std::string id; // The identifier for the type being instantiated
};

} // namespace ast

#endif // NEW_EXPRESSION_HPP

