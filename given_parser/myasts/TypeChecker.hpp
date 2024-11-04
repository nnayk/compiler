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
#include "TypeException.hpp"
#include "CfgProg.hpp"

Env structTLE;
Env globalsTLE;
Env funcTLE;
std::unordered_map<std::string,Env> funcLocalEnvs; // maps function name to local env
ast::Program p;
bool use_ssa = false;

void typecheck(ast::Program &p,std::shared_ptr<Env> tle);
void validate_typeDecls(std::vector<std::shared_ptr<ast::TypeDeclaration>> &typeDecls);
void validate_decls(std::vector<std::shared_ptr<ast::Declaration>> &decls);
void validate_funcs(std::vector<std::shared_ptr<ast::Function>> &funcs);
#endif
