#ifndef DOT_EXPRESSION_HPP
#define DOT_EXPRESSION_HPP

#include "AbstractExpression.hpp"
#include "Expression.hpp"
#include "Register.hpp"
#include <string>
#include <memory>

namespace ast {

class DotExpression : public AbstractExpression, public std::enable_shared_from_this<DotExpression> {
public:
    int offset;
    // Constructor
    DotExpression(int lineNum, std::shared_ptr<Expression> left, const std::string& id);

    // Getter methods for left and id
    std::shared_ptr<Expression> getLeft() const;
    const std::string& getId() const;
    std::string display() const override {
        auto left = this->getLeft()->display();
        return fmt::format("DotExpression(lineNum={},id={},left={}\n)",lineNum,this->getId(),
                            left);
    }
    std::string get_llvm_init(Bblock &block) override;
    std::string get_llvm(Bblock &block) override;
    std::shared_ptr<ast::StructType> getLeftType(); 
    std::shared_ptr<Type> resolveType(Env &env) override;
    std::string get_topmost_id();

private:
    std::shared_ptr<Expression> left_;  // Left expression
    std::string id_;                    // Identifier
};

} // namespace ast

#endif // DOT_EXPRESSION_HPP

