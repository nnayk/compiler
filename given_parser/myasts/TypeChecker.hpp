#include <string>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "Program.hpp"
#include "Parser.hpp"
#include "spdlog/spdlog.h"

std::shared_ptr<std::string> typeCheck(ast::Program &,std::shared_ptr<std::string> msgPtr);
int validate_typeDecls(std::vector<std::shared_ptr<ast::TypeDeclaration>> typeDecls,std::shared_ptr<std::string> msgPtr);
int validate_decls(std::vector<std::shared_ptr<ast::Declaration>> decls,std::shared_ptr<std::string> msgPtr);
int validate_funcs(std::vector<std::shared_ptr<ast::Function>> funcs,std::shared_ptr<std::string> msgPtr);
