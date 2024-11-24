#ifndef LVALUE_ID_HPP
#define LVALUE_ID_HPP

#include "Lvalue.hpp"
#include <string>

namespace ast {

class LvalueId : public Lvalue {
public:
    // Constructor
    LvalueId(int lineNum, const std::string& id);

    // Getter methods
    int getLineNum() const;
    std::string getId() const override;
    std::shared_ptr<Type> resolveType(Env &env) override;
    std::string get_llvm_init(Bblock &block) override;
    std::string get_llvm(Bblock &block) override;
    virtual std::string get_ssa_init(Bblock &block) override;
    virtual std::string get_ssa(Bblock &block) override;
    virtual void resolve_def(std::string &source_immediate) override;
    virtual std::string get_arm_init(Bblock &block) override;

private:
    int lineNum;      // Line number in source code
    std::string id;   // Identifier
};

} // namespace ast

#endif // LVALUE_ID_HPP

