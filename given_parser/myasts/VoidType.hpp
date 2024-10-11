#ifndef VOIDTYPE_HPP
#define VOIDTYPE_HPP

#include "Type.hpp"

namespace ast {

class VoidType : public Type {
    // No additional members or methods are needed for VoidType
	std::string display() const override {
		return fmt::format("VoidType()");
	}
};

} // namespace ast

#endif // VOIDTYPE_HPP

