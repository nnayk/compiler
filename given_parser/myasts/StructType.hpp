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
    StructType(int lineNum, const std::string& name): lineNum(lineNum), name(name) {}
    std::string get_llvm() const override {
        spdlog::debug("inside StructType::{}\n",__func__);
		return fmt::format("ptr",name);
	}
    int alignment() const override {
        return 8;
    };
    std::string default_val() const override {
        return "null";
    };
    
    // Optional: Getters for lineNum and name if needed
    int getLineNum() const { return lineNum; }
    std::string getName() const { return name; }
	std::string display() const override {
		return fmt::format("Structname(line={},struct={})",lineNum,name);
	}
};

} // namespace ast

//Specialize fmt::formatter for StructType
/*
template <>
struct fmt::formatter<ast::StructType> : fmt::formatter<std::string> {
       auto format(const ast::StructType decl, format_context &ctx) const ->decltype(ctx.out()
                  ) {
                  return format_to(ctx.out(), "[StructType()]");
                           }
};
*/
#endif // STRUCTTYPE_HPP

