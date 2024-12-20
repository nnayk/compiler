#include "BinaryExpression.hpp"
#include "Register.hpp"
#include "TypeException.hpp"

extern std::string TAB;
extern bool use_ssa;

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
    //TODO: actually typecheck that left and right are either both ints or both bools
	auto operatorType = this->getOperator();
    if(operatorType==BinaryExpression::Operator::PLUS || operatorType==BinaryExpression::Operator::MINUS || operatorType==BinaryExpression::Operator::TIMES || operatorType==BinaryExpression::Operator::DIVIDE) {
        this->type = std::make_shared<ast::IntType>();
    } else {
        this->type = std::make_shared<ast::BoolType>();
    }
    return this->type;
}

std::string BinaryExpression::get_llvm_init(Bblock &block) {
    spdlog::debug("inside BinaryExpression::{}\n",__func__);
	auto llvm_str = this->getLeft()->get_llvm_init(block);
    llvm_str += this->getRight()->get_llvm_init(block);
	llvm_str += TAB;
    auto operatorType = this->getOperator();
	auto left_llvm = this->getLeft()->get_llvm(block);
	auto right_llvm = this->getRight()->get_llvm(block);
	auto type_llvm = this->getLeft()->type->get_llvm();
	if(!this->result) { 
        assert(!use_ssa);
        this->result = Register::create();
    }
	auto result_llvm = this->result->get_llvm();
    spdlog::debug("result llvm = {}\n",result_llvm);
	std::string operator_llvm = "";
    //std::string extra_str = "";
    //std::shared_ptr<Register> old_result = nullptr;
	switch (operatorType) {
		case BinaryExpression::Operator::PLUS:
			spdlog::debug("The operator is PLUS.");
			operator_llvm = "add";
			break;
		case BinaryExpression::Operator::MINUS:
			spdlog::debug("The operator is MINUS.");
			operator_llvm = "sub";
			break;
		case BinaryExpression::Operator::TIMES:
			spdlog::debug("The operator is TIMES.");
			operator_llvm = "mul";
			break;
		case BinaryExpression::Operator::DIVIDE:
			spdlog::debug("The operator is DIVIDE.");
			operator_llvm = "sdiv";
			break;
		case BinaryExpression::Operator::LT:
			spdlog::debug("The operator is LT.");
			operator_llvm = "icmp slt";
            //old_result = this->result;
            //this->result = Register::create();
            //extra_str = TAB + fmt::format("{} = zext i1 {} to i8\n",this->result->get_llvm(block),old_result->get_llvm(block));
			break;
		case BinaryExpression::Operator::GT:
			spdlog::debug("The operator is GT.");
			operator_llvm = "icmp sgt";
            //old_result = this->result;
            //this->result = Register::create();
            //extra_str = TAB + fmt::format("{} = zext i1 {} to i8\n",this->result->get_llvm(block),old_result->get_llvm(block));
			break;
		case BinaryExpression::Operator::LE:
			spdlog::debug("The operator is LE.");
			operator_llvm = "icmp sle";
            //old_result = this->result;
            //this->result = Register::create();
            //extra_str = TAB + fmt::format("{} = zext i1 {} to i8\n",this->result->get_llvm(block),old_result->get_llvm(block));
			break;
		case BinaryExpression::Operator::GE:
			spdlog::debug("The operator is GE.");
			operator_llvm = "icmp sge";
            //old_result = this->result;
            //this->result = Register::create();
            //extra_str = TAB + fmt::format("{} = zext i1 {} to i8\n",this->result->get_llvm(block),old_result->get_llvm(block));
			break;
		case BinaryExpression::Operator::EQ:
			spdlog::debug("The operator is EQ.");
			operator_llvm = "icmp eq";
            //old_result = this->result;
            //this->result = Register::create();
            //extra_str = TAB + fmt::format("{} = zext i1 {} to i8\n",this->result->get_llvm(block),old_result->get_llvm(block));
			break;
		case BinaryExpression::Operator::NE:
			spdlog::debug("The operator is NE.");
			operator_llvm = "icmp ne";
            //old_result = this->result;
            //this->result = Register::create();
            //extra_str = TAB + fmt::format("{} = zext i1 {} to i8\n",this->result->get_llvm(block),old_result->get_llvm(block));
			break;
		case BinaryExpression::Operator::AND:
			spdlog::debug("The operator is AND.");
			operator_llvm = "and";
            //old_result = this->result;
            //this->result = Register::create();
            //extra_str = TAB + fmt::format("{} = zext i1 {} to i8\n",this->result->get_llvm(),old_result->get_llvm());
			break;
		case BinaryExpression::Operator::OR:
			spdlog::debug("The operator is OR.");
			operator_llvm = "or";
            //old_result = this->result;
            //this->result = Register::create();
            //extra_str = TAB + fmt::format("{} = zext i1 {} to i8\n",this->result->get_llvm(),old_result->get_llvm());
			break;
		default:
			throw TypeException("Unknown operator!");
	} 
	llvm_str += fmt::format("{} = {} {} {}, {}\n",result_llvm,operator_llvm,type_llvm,left_llvm,right_llvm);
    //llvm_str += extra_str;
    return llvm_str;
}

std::string BinaryExpression::get_llvm(Bblock &block) {
    spdlog::debug("inside BinaryExpression::{}\n",__func__);
	return this->result->get_llvm();
}

bool BinaryExpression::is_i1() {
    spdlog::debug("inside BinaryExpression::{}\n",__func__);
    spdlog::debug("line = {}\n",this->getLineNum());
	switch (operatorType) {
		case BinaryExpression::Operator::LT:
		case BinaryExpression::Operator::GT:
		case BinaryExpression::Operator::LE:
		case BinaryExpression::Operator::GE:
		case BinaryExpression::Operator::EQ:
		case BinaryExpression::Operator::NE:
			spdlog::debug("YES i1");
		    return true;
        default:
			spdlog::debug("NO i1");
		    return false;
	} 
    
}

std::string BinaryExpression::zext() {
    spdlog::debug("inside BinaryExpression::{}\n",__func__);
    spdlog::debug("line = {}\n",this->getLineNum());
    auto old_result = this->result;
    this->result = Register::create();
    return TAB + fmt::format("{} = zext i1 {} to i8\n",this->result->get_llvm(),old_result->get_llvm());
}

void BinaryExpression::resolve_uses(Bblock &block) {
    spdlog::debug("inside BinaryExpression::{}\n",__func__);
    left->resolve_uses(block);
    right->resolve_uses(block);
	this->result = Register::create();
    this->result->add_exp(shared_from_this());
    spdlog::debug("chose register {} for BinaryExpression on line {}\n",*this->result,this->getLineNum());
}

std::string BinaryExpression::get_ssa_init(Bblock &block) {
    spdlog::debug("inside BinaryExpression::{}\n",__func__);
    assert(this->result);
    return this->get_llvm_init(block);
}

std::string BinaryExpression::get_ssa(Bblock &block) {
    spdlog::debug("inside BinaryExpression::{}\n",__func__);
    return this->get_llvm(block);
}

// This function assumes get_llvm_init has already been called
std::string BinaryExpression::get_arm_init(Bblock &block) {
    spdlog::debug("inside BinaryExpression::{}\n",__func__);
	auto arm_str = this->getLeft()->get_llvm_init(block);
    arm_str += this->getRight()->get_llvm_init(block);
	arm_str += TAB;
    auto operatorType = this->getOperator();
	auto left_arm = this->getLeft()->get_llvm(block);
	auto right_arm = this->getRight()->get_llvm(block);
	auto type_arm = this->getLeft()->type->get_llvm();
	if(!this->result) { 
        assert(!use_ssa);
        this->result = Register::create();
    }
	auto result_arm = this->result->get_arm();
    spdlog::debug("result arm = {}\n",result_arm);
	std::string operator_arm = "";
    // TODO: add special handling for binary bool expr
    //std::string extra_str = "";
    //std::shared_ptr<Register> old_result = nullptr;
	switch (operatorType) {
		case BinaryExpression::Operator::PLUS:
			spdlog::debug("The operator is PLUS.");
			operator_arm = "add";
			break;
		case BinaryExpression::Operator::MINUS:
			spdlog::debug("The operator is MINUS.");
			operator_arm = "sub";
			break;
		case BinaryExpression::Operator::TIMES:
			spdlog::debug("The operator is TIMES.");
			operator_arm = "mul";
			break;
		case BinaryExpression::Operator::DIVIDE:
			spdlog::debug("The operator is DIVIDE.");
			operator_arm = "sdiv";
			break;
		case BinaryExpression::Operator::LT:
			spdlog::debug("The operator is LT.");
			operator_arm = "icmp slt";
            //old_result = this->result;
            //this->result = Register::create();
            //extra_str = TAB + fmt::format("{} = zext i1 {} to i8\n",this->result->get_arm(block),old_result->get_llvm(block));
			break;
		case BinaryExpression::Operator::GT:
			spdlog::debug("The operator is GT.");
			operator_arm = "icmp sgt";
            //old_result = this->result;
            //this->result = Register::create();
            //extra_str = TAB + fmt::format("{} = zext i1 {} to i8\n",this->result->get_arm(block),old_result->get_llvm(block));
			break;
		case BinaryExpression::Operator::LE:
			spdlog::debug("The operator is LE.");
			operator_arm = "icmp sle";
            //old_result = this->result;
            //this->result = Register::create();
            //extra_str = TAB + fmt::format("{} = zext i1 {} to i8\n",this->result->get_arm(block),old_result->get_llvm(block));
			break;
		case BinaryExpression::Operator::GE:
			spdlog::debug("The operator is GE.");
			operator_arm = "icmp sge";
            //old_result = this->result;
            //this->result = Register::create();
            //extra_str = TAB + fmt::format("{} = zext i1 {} to i8\n",this->result->get_arm(block),old_result->get_llvm(block));
			break;
		case BinaryExpression::Operator::EQ:
			spdlog::debug("The operator is EQ.");
			operator_arm = "icmp eq";
            //old_result = this->result;
            //this->result = Register::create();
            //extra_str = TAB + fmt::format("{} = zext i1 {} to i8\n",this->result->get_arm(block),old_result->get_llvm(block));
			break;
		case BinaryExpression::Operator::NE:
			spdlog::debug("The operator is NE.");
			operator_arm = "icmp ne";
            //old_result = this->result;
            //this->result = Register::create();
            //extra_str = TAB + fmt::format("{} = zext i1 {} to i8\n",this->result->get_arm(block),old_result->get_llvm(block));
			break;
		case BinaryExpression::Operator::AND:
			spdlog::debug("The operator is AND.");
			operator_arm = "and";
            //old_result = this->result;
            //this->result = Register::create();
            //extra_str = TAB + fmt::format("{} = zext i1 {} to i8\n",this->result->get_arm(),old_result->get_llvm());
			break;
		case BinaryExpression::Operator::OR:
			spdlog::debug("The operator is OR.");
			operator_arm = "or";
            //old_result = this->result;
            //this->result = Register::create();
            //extra_str = TAB + fmt::format("{} = zext i1 {} to i8\n",this->result->get_arm(),old_result->get_llvm());
			break;
		default:
			throw TypeException("Unknown operator!");
	} 
	arm_str += fmt::format("{} {}, {}, {}\n",operator_arm,result_arm,left_arm,right_arm);
    //arm_str += extra_str;
    return arm_str;
}

void BinaryExpression::replace_reg(std::shared_ptr<Register> target,std::shared_ptr<Register> sub) {
    spdlog::debug("inside BinaryExpression::{}\n",__func__);
    this->left->replace_reg(target,sub);
    this->right->replace_reg(target,sub);
    this->result = sub;
}

}  // namespace ast
