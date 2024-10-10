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
        return 1;
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
    } else if(!validate_decls(p.decls,msgPtr)) {
        spdlog::debug("issue with globals, msg = {}",*msgPtr);
        return msgPtr;
    } else if(!validate_funcs(p.funcs,msgPtr)) {
        spdlog::debug("issue with functions, msg = {}",*msgPtr);
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
	// Check that struct names are unique
	std::unordered_set<std::string> structNames;
	std::unordered_set<std::string> fieldNames;
	for (const auto& typeDecl : typeDecls) {
        if (structNames.find(typeDecl->name) != structNames.end()) {
            *msgPtr = "Duplicate type name found: " + typeDecl->name;
            return 0;  // Return failure
        }
		// Check that each field in the TypeDeclaration has a unique name
        std::unordered_set<std::string> fieldNames;
        for (const auto& field : typeDecl->fields) {
            if (fieldNames.find(field.getName()) != fieldNames.end()) {
                *msgPtr = "Duplicate field name '" + field.getName() + "' found in type: " + typeDecl->name;
                return 0;  // Return failure
            }
            fieldNames.insert(field.getName());
        }
		fieldNames.clear();
        // Add the name to the set
        structNames.insert(typeDecl->name);
    }
	// Check that each struct has unique field names
    *msgPtr = "abc";
    return 1;
}

/*
Validate that all the globals have unique names
*/
//TODO: change it to accept a reference to a list of typedecls
int validate_decls(std::vector<std::shared_ptr<ast::Declaration>> decls,
					   std::shared_ptr<std::string> msgPtr) {
	// Check that global var names are unique
	std::unordered_set<std::string> globalNames;
	for (const auto& decl : decls) {
		if (globalNames.find(decl->getName()) != globalNames.end()) {
		 *msgPtr = "Duplicate declaration name found: " + decl->getName();
		 return 0;  // Return failure
		}
		globalNames.insert(decl->getName());	
	}
	return 1;
}

/*
Validates all the functions for the following:
1. each function's name is unique
2. unique param names for each function
3. unique local var names for each function
4. typecheck body for each function
*/
//TODO: change it to accept a reference to a list of typedecls
int validate_funcs(std::vector<std::shared_ptr<ast::Function>> funcs,
				   std::shared_ptr<std::string> msgPtr) {
	// Check that function names are unique
	std::unordered_set<std::string> funcNames;
	std::unordered_set<std::string> paramNames;
	std::unordered_set<std::string> localNames;
	for(const auto& func : funcs) {
		spdlog::debug("func name = {}",func->name);
		if(funcNames.find(func->name) != funcNames.end()) {
	 		*msgPtr = "Duplicate function name found: " + func->name;
		 	return 0;  // Return failure
	 	}
		// Check param names are unique
        for (const auto& param : func->params) {
            if (paramNames.find(param.getName()) != paramNames.end()) {
                *msgPtr = "Duplicate param name '" + param.getName() + "' found:" + func->name;
                return 0;  // Return failure
            }
            paramNames.insert(param.getName());
        }
		// Check local names are unique (and that there's no overlap w/param names)
        for (const auto& local : func->locals) {
            if (localNames.find(local.getName()) != localNames.end()) {
                *msgPtr = "Duplicate local name '" + local.getName() + "' found:" + func->name;
                return 0;  // Return failure
            } else if (paramNames.find(local.getName()) != paramNames.end()) {
                *msgPtr = "Duplicate local name (existing param!) '" + local.getName() + "' found:" + func->name;
                return 0;  // Return failure
            }
            localNames.insert(local.getName());
        }
		paramNames.clear();
		localNames.clear();
		// Check local var names are unique
		funcNames.insert(func->name);
    }
	return 1;	
}
