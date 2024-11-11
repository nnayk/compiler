#ifndef LVALUE_DOT_HPP
#define LVALUE_DOT_HPP

#include "Lvalue.hpp"
#include "Expression.hpp"
#include <memory>

namespace ast {

class LvalueDot : public Lvalue, public std::enable_shared_from_this<LvalueDot> {
public:
    int lineNum;                          // Line number in source code
    std::shared_ptr<Lvalue> left;     // Left expression
    std::string id;                       // Identifier of the member being accessed
   // TODO:: add an offset attr or get offset function (attr is more efficient ofc)
    int offset;
    // Constructor
    LvalueDot(int lineNum, std::shared_ptr<Lvalue> left, const std::string& id);

    // Getter methods
    int getLineNum() const;
    std::shared_ptr<Lvalue> getLeft() const;
    std::shared_ptr<Type> resolveType(Env &env) override;
    std::string getId() const override;
    std::string get_llvm_init(Bblock &block) override;
    std::string get_llvm(Bblock &block) override;
    std::shared_ptr<ast::StructType> getLeftType();
    std::string get_topmost_id();
    virtual void resolve_def() override;
};

} // namespace ast

#endif // LVALUE_DOT_HPP

