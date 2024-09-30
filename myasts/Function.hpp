#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <string>
#include <list>
#include <memory>
#include "Type.hpp"
#include "Declaration.hpp"
#include "Statement.hpp"

namespace ast {

class Function {
public:
    // Constructor
    Function(int lineNum, const std::string& name,
             const std::list<std::shared_ptr<Declaration>>& params,
             std::shared_ptr<Type> retType,
             const std::list<std::shared_ptr<Declaration>>& locals,
             std::shared_ptr<Statement> body);

    // Getters for member variables
    int getLineNum() const;
    const std::string& getName() const;
    const std::list<std::shared_ptr<Declaration>>& getParams() const;
    std::shared_ptr<Type> getRetType() const;
    const std::list<std::shared_ptr<Declaration>>& getLocals() const;
    std::shared_ptr<Statement> getBody() const;

private:
    int lineNum;  // Line number of the function definition
    std::string name;  // Name of the function
    std::list<std::shared_ptr<Declaration>> params;  // Function parameters
    std::shared_ptr<Type> retType;  // Return type
    std::list<std::shared_ptr<Declaration>> locals;  // Local declarations
    std::shared_ptr<Statement> body;  // Function body
};

} // namespace ast

#endif // FUNCTION_HPP

