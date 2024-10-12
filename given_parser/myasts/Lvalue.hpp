 #ifndef LVALUE_HPP
 #define LVALUE_HPP
 #include <spdlog/spdlog.h>
 #include "Expression.hpp"
#include "Types.hpp"
#include <memory>
 namespace ast {

 class Lvalue {
 public:
     // Virtual destructor for proper cleanup of derived classes
      virtual ~Lvalue() = default;
      virtual std::string getId() const = 0;
      virtual std::shared_ptr<Type> resolveType() const = 0;
 };
 }  // namespace ast

 #endif
