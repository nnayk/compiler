#include "TypeDeclaration.hpp"
#include "Types.hpp"

namespace ast {

TypeDeclaration::TypeDeclaration(int lineNum, const std::string& name, const std::vector<Declaration>& fields)
    : lineNum(lineNum), name(name), fields(fields) {
}

std::string TypeDeclaration::get_llvm() {
    return fmt::format("%struct.{}",this->name);
}

std::string TypeDeclaration::get_llvm_init() {
    std::string llvm_str = fmt::format("%struct.{} = type {{ ",this->name);
    int index=0;
    auto fields_size = this->fields.size();
    for(auto attr : this->fields) {
        llvm_str += attr.getType()->get_llvm();
        if(index<fields_size-1) {
            llvm_str += ", ";
        } else {
            llvm_str += " }";
        }
        index++;
    }
    return llvm_str;
}

} // namespace ast

