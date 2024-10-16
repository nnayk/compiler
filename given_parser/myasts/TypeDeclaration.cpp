#include "TypeDeclaration.hpp"

namespace ast {

TypeDeclaration::TypeDeclaration(int lineNum, const std::string& name, const std::vector<Declaration>& fields)
    : lineNum(lineNum), name(name), fields(fields) {
}

std::string TypeDeclaration::get_llvm() {
    std::string llvm_str = fmt::format("%%struct.{} = type {{ ",this->name);
    int index=0;
    auto fields_size = this->fields.size();
    for(auto attr : this->fields) {
        if(index<fields_size-1) {
            llvm_str += fmt::format("{}, ",attr.get_llvm());
        } else {
            llvm_str += fmt::format("{} }}",attr.get_llvm());
        }
        index++;
    }
    return llvm_str;
}

} // namespace ast

