#include "TypeChecker.hpp"
#include "Env.hpp"
#include <unordered_set>


int main(int argc, char *argv[]) {
    spdlog::set_level(spdlog::level::debug); // Set global log level to debug
    spdlog::debug("Reading file {}",argv[1]);
    std::ifstream jsonStream(argv[1]); // Open a file for reading
    if (!jsonStream.is_open()) {
        std::cerr << "Error: Could not open the file " << argv[1] << "!" << std::endl;
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
    p.decls = parse_decls(data["declarations"]);
    spdlog::debug("{} decls",p.decls.size());
    for(auto d: p.decls)
    {
        spdlog::info(*d);
    }
    p.typeDecls = parse_typeDecls(data["types"]); 
    spdlog::debug("{} structs",p.typeDecls.size());
    for(auto d: p.typeDecls)
    {
        spdlog::info(*d);
    }
    p.funcs = parse_funcs(data["functions"]);
    spdlog::debug("{} functions",p.funcs.size());
    for(auto f: p.funcs)
    {
        spdlog::info(*f);
    }
    jsonStream.close(); // Always close the file when done
    
    std::shared_ptr<std::string> errPtr = std::make_shared<std::string>("");
    typeCheck(p,errPtr);
    if(errPtr->length() > 0) { 
        std::cerr << *errPtr << std::endl;
        return 9;
    } else {
        spdlog::debug("typechecking passed");
    }
    return 0;
}

/*
 * Performs static type checking of the given program
 * Returns:
 * empty string on success
 * error message string on failure
*/
std::shared_ptr<std::string> typeCheck(ast::Program &p,std::shared_ptr<std::string> msgPtr) {
    spdlog::info("inside {}",__func__);
    if(!validate_typeDecls(p.typeDecls,msgPtr)) {
        spdlog::debug("issue with globals, msg = {}",*msgPtr);
        return msgPtr;
    }
    return msgPtr;
}

/*
Validate that all the structs have unique names and that the attributes in each
struct has a unique name
*/
//TODO: change it to accept a reference to a list of typedecls
int validate_typeDecls(std::vector<std::shared_ptr<ast::TypeDeclaration>> typeDecls,
					   std::shared_ptr<std::string> msgPtr) {
	std::unordered_set<std::string> uniqueNames;
	for (const auto& typeDecl : typeDecls) {
        // Check if the name is already in the set
        if (uniqueNames.find(typeDecl->name) != uniqueNames.end()) {
            *msgPtr = "Duplicate type name found: " + typeDecl->name;
            return 0;  // Return failure
        }

        // Add the name to the set
        uniqueNames.insert(typeDecl->name);
    }
    *msgPtr = "abc";
    return 1;
}
