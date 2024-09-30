#ifndef STRUCTTYPE_HPP
#define STRUCTTYPE_HPP

#include <string>
#include "Type.hpp"

namespace ast {

class StructType : public Type {
private:
    int lineNum;
    std::string name;

public:
    StructType(int lineNum, const std::string& name);
    
    // Optional: Getters for lineNum and name if needed
    int getLineNum() const { return lineNum; }
    std::string getName() const { return name; }
};

} // namespace ast

#endif // STRUCTTYPE_HPP

