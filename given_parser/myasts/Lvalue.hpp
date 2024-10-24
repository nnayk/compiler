 #ifndef LVALUE_HPP
 #define LVALUE_HPP
 #include <spdlog/spdlog.h>
 #include "Expression.hpp"
#include "Types.hpp"
#include "Register.hpp"
#include <memory>
extern Env structTLE; 
extern Env globalsTLE; 
extern Env funcTLE; 

namespace ast {

 class Lvalue {
 public:
     std::shared_ptr<Register> result; // register where the lvalue is stored
     std::shared_ptr<ast::Type> type = nullptr; 
     // Virtual destructor for proper cleanup of derived classes
      virtual ~Lvalue() = default;
      virtual std::string getId() const = 0;
      virtual std::shared_ptr<Type> resolveType(Env &env) = 0;
      virtual std::string get_llvm() const = 0;
 };
 }  // namespace ast

 #endif
