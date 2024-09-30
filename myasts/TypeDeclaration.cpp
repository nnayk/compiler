#include "TypeDeclaration.hpp"

namespace ast {

TypeDeclaration::TypeDeclaration(int lineNum, const std::string& name, const std::vector<Declaration>& fields)
    : lineNum(lineNum), name(name), fields(fields) {
}

} // namespace ast

