#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "Program.hpp"
#include "Parser.hpp"
#include "spdlog/spdlog.h"

int main(int argc, char *argv[]) {
    spdlog::set_level(spdlog::level::debug); // Set global log level to debug
    std::ifstream jsonStream(argv[1]); // Open a file for reading
    if (!jsonStream.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return 1;
    }
    nlohmann::json data = nlohmann::json::parse(jsonStream);
    // delete this, was debugging
    /*
    for (json::iterator it = data.begin(); it != data.end(); ++it) {
       std::cout << it.key() << " : " << it.value() << "\n";
       std::cout << data[it.key()] << std::endl;
    }
    */
    ast::Program p;
    // special iterator member functions for objects
    // parse the types
    //p.typeDecls = parse_typeDecls(data["types"]); // FIX THE ITERATION FOR THIS + funcs
    p.decls = parse_decls(data["declarations"]);
    //p.funcs = parse_funcs(data["functions"]);
    // parse the declarations
    // parse the types
    /*
    std::string line;
    while (std::getline(jsonStream, line)) {
        std::cout << line << std::endl; // Print each line from the file
    }
    */
    jsonStream.close(); // Always close the file when done
    return 0;
}
