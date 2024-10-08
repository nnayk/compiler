#include "TypeDeclaration.hpp"
#include "Declaration.hpp"
#include "Function.hpp"
#include "BlockStatement.hpp"
#include "AssignmentStatement.hpp"
#include "PrintStatement.hpp"
#include "ConditionalStatement.hpp"
#include "WhileStatement.hpp"
#include "DeleteStatement.hpp"
#include "ReturnStatement.hpp"
#include "ReturnEmptyStatement.hpp"
#include "InvocationStatement.hpp"
//#include "AllExpressions.hpp"
#include "LvalueId.hpp"
#include "LvalueDot.hpp"
#include "LvalueIndex.hpp"
#include <nlohmann/json.hpp>

std::vector<ast::TypeDeclaration*> parse_typeDecls(const nlohmann::json& json_object);
std::vector<ast::Declaration*> parse_decls(const nlohmann::json& json_object);
std::vector<ast::Function*> parse_funcs(const nlohmann::json& json_object);
std::shared_ptr<ast::Type> createType(const std::string typeStr, const std::string var, const int lineNum);
std::shared_ptr<ast::Statement> parse_statement(const nlohmann::json &json);
std::shared_ptr<ast::AssignmentStatement> parse_assignment(const nlohmann::json &json);
std::shared_ptr<ast::Lvalue> parse_lvalue(const nlohmann::json &json);
std::shared_ptr<ast::Expression> parse_expr(const nlohmann::json &json);
std::shared_ptr<ast::LvalueId> parse_lvalueId(int lineNum,const nlohmann::json &json);
std::shared_ptr<ast::BlockStatement> parse_block(const nlohmann::json &json);
std::shared_ptr<ast::PrintStatement> parse_print(const nlohmann::json &json);
std::shared_ptr<ast::ConditionalStatement> parse_conditional(const nlohmann::json &json);
std::shared_ptr<ast::WhileStatement> parse_loop(const nlohmann::json &json);
std::shared_ptr<ast::DeleteStatement> parse_delete(const nlohmann::json &json);
std::shared_ptr<ast::ReturnStatement> parse_nonempty_return(const nlohmann::json &json);
std::shared_ptr<ast::InvocationStatement> parse_invocation(const nlohmann::json &json);
