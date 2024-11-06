#include "NullExpression.hpp"

namespace ast 
{
    std::string NullExpression::get_llvm(Bblock &block) {
        return "null";
    }
}
