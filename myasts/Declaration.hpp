#ifndef DECLARATION_HPP
#define DECLARATION_HPP

#include <string>
#include <memory>
#include "Type.hpp"  // Assuming you have a Type class defined

namespace ast {

class Declaration {
public:
    // Constructor
    Declaration(int lineNum, std::shared_ptr<Type> type, const std::string& name);

    // Getters
    int getLineNum() const;
    std::shared_ptr<Type> getType() const;
    const std::string& getName() const;

private:
    int lineNum_;
    std::shared_ptr<Type> type_;
    std::string name_;
};

} // namespace ast

#endif // DECLARATION_HPP

