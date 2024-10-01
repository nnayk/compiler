#include "TypeDeclaration.hpp"
#include <nlohmann/json.hpp>

std::vector<ast::TypeDeclaration*> parse_types(const nlohmann::json& json_object);
