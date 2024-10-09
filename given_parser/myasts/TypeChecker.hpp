#include <string>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "Program.hpp"
#include "Parser.hpp"
#include "spdlog/spdlog.h"

std::shared_ptr<std::string> typeCheck(ast::Program &,std::shared_ptr<std::string> msgPtr);
int validate_typeDecls(ast::Program &p,std::shared_ptr<std::string> msgPtr);
