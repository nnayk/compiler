#ifndef NULL_TYPE_HPP
#define NULL_TYPE_HPP

#include "Type.hpp"

namespace ast {

class NullType : public Type {
public:
    // Constructor
    NullType() {}
    
    // Destructor
    virtual ~NullType() = default; // Default virtual destructor

	std::string display() const override {
		return fmt::format("NullType()");
	}
    
    std::string get_llvm() const override {
		return "null";
	}
};

} // namespace ast

#endif // NULL_TYPE_HPP

