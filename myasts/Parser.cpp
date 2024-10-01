#include "Parser.hpp"
#include <iostream> //DELETE
#include "spdlog/spdlog.h" 
std::vector<ast::TypeDeclaration*> parse_types(const nlohmann::json& data) {
    spdlog::info("inside parse_types()");
    std::vector<ast::TypeDeclaration*> type_declarations;
    // Logic for populating type_declarations from json_object
    //     // Dynamically allocate TypeDeclaration objects and add them to the vector
    for (nlohmann::json::const_iterator it = data.begin(); it != data.end(); ++it) {
        std::cout << it.key() << " : " << it.value() << "\n" << std::endl;
        //type_declarations.push_back(new TypeDeclaration(/* arguments */));
    }
    return type_declarations;     
}
