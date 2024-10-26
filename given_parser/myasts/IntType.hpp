#ifndef INT_TYPE_HPP
#define INT_TYPE_HPP

#include "Type.hpp"

namespace ast {

class IntType : public Type {
public:
    // Constructor
    IntType() {}
    
    // Destructor
    virtual ~IntType() = default; // Default virtual destructor

	std::string display() const override {
		return fmt::format("IntType()");
	}
	
    std::string get_llvm() const override {
        spdlog::debug("inside IntType::{}\n",__func__);
		return "i64";
	}
    
    int alignment() const override {
        return 8;
    };
    std::string default_val() const override {
        return "0";
    };
};

} // namespace ast

#endif // INT_TYPE_HPP

