#include "TypeDeclaration.hpp"
#include "Declaration.hpp"
#include "Function.hpp"
#include <nlohmann/json.hpp>

std::vector<ast::TypeDeclaration*> parse_typeDecls(const nlohmann::json& json_object);
std::vector<ast::Declaration*> parse_decls(const nlohmann::json& json_object);
std::vector<ast::Function*> parse_funcs(const nlohmann::json& json_object);
std::shared_ptr<ast::Type> createType(const std::string typeStr, const std::string var, const int lineNum);
