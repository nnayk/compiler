#include "NullExpression.hpp"

namespace ast 
{
    std::string NullExpression::get_llvm() {
        return "null";
    }
}
