#ifndef BOOLTYPE_HPP
#define BOOLTYPE_HPP

#include "Type.hpp"

namespace ast {

class BoolType : public Type {
public:
    // Constructor
    BoolType() = default;

    // Destructor
    virtual ~BoolType() = default;
	std::string display() const override {
		return fmt::format("BoolType()");
	}
	std::string get_llvm() const override {
        spdlog::debug("inside BoolType::{}\n",__func__);
		return "i8";
	}
    int alignment() const override {
        return 1;
    };
    std::string default_val() const override {
        return "0";
    };
};

} // namespace ast

#endif // BOOLTYPE_HPP

