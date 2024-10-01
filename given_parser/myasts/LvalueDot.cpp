#include "LvalueDot.hpp"

namespace ast {

// Constructor
LvalueDot::LvalueDot(int lineNum, std::shared_ptr<Expression> left, const std::string& id)
    : lineNum(lineNum), left(left), id(id) {}

// Getter methods
int LvalueDot::getLineNum() const {
    return lineNum;
}

std::shared_ptr<Expression> LvalueDot::getLeft() const {
    return left;
}

std::string LvalueDot::getId() const {
    return id;
}

} // namespace ast

