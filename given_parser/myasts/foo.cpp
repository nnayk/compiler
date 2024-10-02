#include "Declaration.hpp"
#include <spdlog/spdlog.h>

int main() {
        auto type = std::make_shared<ast::Type>();
            ast::Declaration decl(1, type, "myVar");

                spdlog::info("{}", decl);
                     }
