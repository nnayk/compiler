#include <string>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "Program.hpp"
#include "Parser.hpp"
#include "spdlog/spdlog.h"

std::string typeCheck(ast::Program &p);
