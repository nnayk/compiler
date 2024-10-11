#ifndef TYPECHECKER_HPP_HPP
#define TYPECHECKER_HPP_HPP
#include <string>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "Program.hpp"
#include "Parser.hpp"
#include "spdlog/spdlog.h"
#include "Env.hpp"
#include "Types.hpp"
std::shared_ptr<std::string> typeCheck(ast::Program &,std::shared_ptr<std::string> msgPtr,std::shared_ptr<Env> tle);
int validate_typeDecls(std::vector<std::shared_ptr<ast::TypeDeclaration>> typeDecls,std::shared_ptr<std::string> msgPtr,std::shared_ptr<Env> tle);
int validate_decls(std::vector<std::shared_ptr<ast::Declaration>> decls,std::shared_ptr<std::string> msgPtr,std::shared_ptr<Env> tle);
int validate_funcs(std::vector<std::shared_ptr<ast::Function>> funcs,std::shared_ptr<std::string> msgPtr,std::shared_ptr<Env> tle);
void typecheck_funcs(std::vector<std::shared_ptr<ast::Function>> funcs,std::shared_ptr<Env> tle);
#endif
