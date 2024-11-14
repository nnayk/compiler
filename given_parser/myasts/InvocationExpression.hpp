#ifndef INVOCATION_EXPRESSION_HPP
#define INVOCATION_EXPRESSION_HPP

#include "AbstractExpression.hpp"
#include <string>
#include <vector>
#include <memory>
#include "Program.hpp"

extern ast::Program p;

namespace ast {

class InvocationExpression : public AbstractExpression {
public:
    std::string name; // The name of the invoked function
    std::vector<std::shared_ptr<Expression>> arguments; // List of arguments
    // Constructor
    InvocationExpression(int lineNum, const std::string& name,
                        const std::vector<std::shared_ptr<Expression>>& arguments);
	std::shared_ptr<Type> resolveType(Env &env) override;
    // Getter for the name
    std::string getName() const;

    // Getter for the arguments
    std::vector<std::shared_ptr<Expression>> getArguments() const;
    std::string display() const override {
        auto output = fmt::format("InvocationExpression(lineNum={},func={},args=(",lineNum,name);
        for(auto arg : arguments) {
           output+=fmt::format("{},",*arg); 
        }
        output+="\n";
        return output;
    }
    std::string get_llvm_init(Bblock &block) override;
    std::string get_llvm(Bblock &block) override;
    virtual std::string get_ssa_init(Bblock &block) override;
    virtual std::string get_ssa(Bblock &block) override;
    void resolve_uses(Bblock &block) override;
};

} // namespace ast

#endif // INVOCATION_EXPRESSION_HPP

