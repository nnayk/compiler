 #ifndef LVALUE_HPP
 #define LVALUE_HPP
 #include <spdlog/spdlog.h>
 #include "Expression.hpp"
#include <memory>
 namespace ast {

 class Lvalue {
 public:
     // Virtual destructor for proper cleanup of derived classes
     virtual ~Lvalue() = default;
 };
 }  // namespace ast

 #endif
