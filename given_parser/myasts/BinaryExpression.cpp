#include "BinaryExpression.hpp"
#include "Register.hpp"
#include "TypeException.hpp"

extern std::string TAB;

namespace ast {

// Private constructor definition
BinaryExpression::BinaryExpression(int lineNum, Operator operatorType,
                                   std::shared_ptr<Expression> left,
                                   std::shared_ptr<Expression> right)
    : AbstractExpression(lineNum), operatorType(operatorType), left(left), right(right) {}

// Static factory method definition
std::shared_ptr<BinaryExpression> BinaryExpression::create(int lineNum, const std::string& opStr,
                                                          std::shared_ptr<Expression> left,
                                                          std::shared_ptr<Expression> right) {
    if (opStr == "*") {
        return std::shared_ptr<BinaryExpression>(new BinaryExpression(lineNum, Operator::TIMES, left, right));
    } else if (opStr == "/") {
        return std::shared_ptr<BinaryExpression>(new BinaryExpression(lineNum, Operator::DIVIDE, left, right));
    } else if (opStr == "+") {
        return std::shared_ptr<BinaryExpression>(new BinaryExpression(lineNum, Operator::PLUS, left, right));
    } else if (opStr == "-") {
        return std::shared_ptr<BinaryExpression>(new BinaryExpression(lineNum, Operator::MINUS, left, right));
    } else if (opStr == "<") {
        return std::shared_ptr<BinaryExpression>(new BinaryExpression(lineNum, Operator::LT, left, right));
    } else if (opStr == "<=") {
        return std::shared_ptr<BinaryExpression>(new BinaryExpression(lineNum, Operator::LE, left, right));
    } else if (opStr == ">") {
        return std::shared_ptr<BinaryExpression>(new BinaryExpression(lineNum, Operator::GT, left, right));
    } else if (opStr == ">=") {
        return std::shared_ptr<BinaryExpression>(new BinaryExpression(lineNum, Operator::GE, left, right));
    } else if (opStr == "==") {
        return std::shared_ptr<BinaryExpression>(new BinaryExpression(lineNum, Operator::EQ, left, right));
    } else if (opStr == "!=") {
        return std::shared_ptr<BinaryExpression>(new BinaryExpression(lineNum, Operator::NE, left, right));
    } else if (opStr == "&&") {
        return std::shared_ptr<BinaryExpression>(new BinaryExpression(lineNum, Operator::AND, left, right));
    } else if (opStr == "||") {
        return std::shared_ptr<BinaryExpression>(new BinaryExpression(lineNum, Operator::OR, left, right));
    } else {
        throw std::invalid_argument("Invalid operator string: " + opStr);
    }
}

std::shared_ptr<ast::Type> BinaryExpression::resolveType(Env &env) {
	auto left_type = this->getLeft()->resolveType(env);
	auto right_type = this->getRight()->resolveType(env);
	assert(typeid(left_type) == typeid(right_type));
	this->type = left_type;
	return this->type;
}

std::string BinaryExpression::get_llvm_init() {
    auto llvm_str = this->getLeft()->get_llvm_init();
    llvm_str += this->getRight()->get_llvm_init();
	llvm_str += TAB;
    auto operatorType = this->getOperator();
	auto left_llvm = this->getLeft()->get_llvm();
	auto right_llvm = this->getRight()->get_llvm();
	auto type_llvm = this->type->get_llvm();
	this->result = Register::create();
	auto result_llvm = this->result->get_llvm();
	switch (operatorType) {
        case BinaryExpression::Operator::PLUS:
            spdlog::debug("The operator is PLUS.");
			llvm_str += fmt::format("{} = add {} {}, {}\n",result_llvm,type_llvm,left_llvm,right_llvm); 
            break;
        case BinaryExpression::Operator::MINUS:
            spdlog::debug("The operator is MINUS.");
            break;
        case BinaryExpression::Operator::TIMES:
            spdlog::debug("The operator is TIMES.");
            break;
        case BinaryExpression::Operator::DIVIDE:
            spdlog::debug("The operator is DIVIDE.");
            break;
        case BinaryExpression::Operator::LT:
            spdlog::debug("The operator is LT.");
            break;
        case BinaryExpression::Operator::GT:
            spdlog::debug("The operator is GT.");
            break;
        case BinaryExpression::Operator::LE:
            spdlog::debug("The operator is LE.");
            break;
        case BinaryExpression::Operator::GE:
            spdlog::debug("The operator is GE.");
            break;
        case BinaryExpression::Operator::EQ:
            spdlog::debug("The operator is EQ.");
            break;
        case BinaryExpression::Operator::NE:
            spdlog::debug("The operator is NE.");
            break;
        case BinaryExpression::Operator::AND:
            spdlog::debug("The operator is AND.");
            break;
        case BinaryExpression::Operator::OR:
            spdlog::debug("The operator is OR.");
            break;
        default:
			throw TypeException("Unknown operator!"); 
	} 
    return llvm_str;
}

std::string BinaryExpression::get_llvm() {
	return this->result->get_llvm();
}

}  // namespace ast
