#include "TypeDeclaration.hpp"
#include "Declaration.hpp"
#include "Function.hpp"
#include "BlockStatement.hpp"
#include "AssignmentStatement.hpp"
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
