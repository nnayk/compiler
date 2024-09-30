#include "StructType.hpp"

namespace ast {

StructType::StructType(int lineNum, const std::string& name)
    : lineNum(lineNum), name(name) {
}

} // namespace ast

