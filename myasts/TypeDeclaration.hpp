#ifndef TYPEDECLARATION_HPP
#define TYPEDECLARATION_HPP

#include <string>
#include <vector>
#include "Declaration.hpp"

namespace ast {

class TypeDeclaration {
private:
    int lineNum;
    std::string name;
    std::vector<Declaration> fields;

public:
    TypeDeclaration(int lineNum, const std::string& name, const std::vector<Declaration>& fields);
};

} // namespace ast

#endif // TYPEDECLARATION_HPP

