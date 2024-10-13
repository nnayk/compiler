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
    std::shared_ptr<Type> resolveType(Env &env) const override;

private:
    int lineNum;      // Line number in source code
    std::string id;   // Identifier
};

} // namespace ast

#endif // LVALUE_ID_HPP

