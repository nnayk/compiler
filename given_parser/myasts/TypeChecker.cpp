#include "TypeChecker.hpp"
#include "Env.hpp"
#include <unordered_set>

int main(int argc, char *argv[]) {
    spdlog::set_level(spdlog::level::debug); // Set global log level to debug
    //spdlog::debug("Reading file {}",argv[1]);
    //std::ifstream jsonStream(argv[1]); // Open a file for reading
    std::ifstream jsonStream("stats.json");
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
        spdlog::debug("dec name = {}",d->name);
        spdlog::info(*d);
    }
    p.funcs = parse_funcs(data["functions"]);
    spdlog::debug("{} functions",p.funcs.size());
    for(auto f: p.funcs)
    {
        spdlog::debug("func name = {}",f->name);
        spdlog::info(*f);
    }
    jsonStream.close(); // Always close the file when done
    
    std::shared_ptr<std::string> errPtr = std::make_shared<std::string>("");
	std::shared_ptr<Env> tle = std::make_shared<Env>();
    typecheck(p,tle);
    spdlog::debug("typechecking passed");
    return 0;
}

/*
 * Performs static type checking of the given program
 * Returns:
 * empty string on success
 * error message string on failure
*/
void typecheck(ast::Program &p,std::shared_ptr<Env> tle) {
    spdlog::info("inside {}",__func__);
    validate_typeDecls(p.typeDecls);
    spdlog::debug("Struct TLE: {}",structTLE);
    validate_decls(p.decls);
    spdlog::debug("Global vars TLE: {}",globalsTLE);
    validate_funcs(p.funcs);
    spdlog::debug("Func TLE: {}",funcTLE);
}

/*
Validate that all the structs have unique names and that the attributes in each
struct has a unique name
*/
//TODO: change it to accept a reference to a list of typedecls
void validate_typeDecls(std::vector<std::shared_ptr<ast::TypeDeclaration>> &typeDecls) {
	// Check that struct names are unique
	std::unordered_set<std::string> structNames;
	std::unordered_set<std::string> fieldNames;
    std::shared_ptr<StructEntry> structE;
    std::shared_ptr<AttrEntry> attrE;
	for(const auto& typeDecl : typeDecls) {
		structE = std::make_shared<StructEntry>(std::make_shared<ast::StructType>(typeDecl->lineNum,typeDecl->name)); 
        if (structNames.find(typeDecl->name) != structNames.end()) {
            throw TypeException(fmt::format("Duplicate type name found: {}", typeDecl->name));
        }
		// Check that each field in the TypeDeclaration has a unique name
        std::unordered_set<std::string> fieldNames;
        int offset = 0;
        structE->attrEnv = std::make_shared<Env>();
        for (const auto& field : typeDecl->fields) {
            if (fieldNames.find(field.getName()) != fieldNames.end()) {
                throw TypeException(fmt::format("Duplicate field name {} found in type: {}", field.getName(), typeDecl->name));
            }
            attrE = std::make_shared<AttrEntry>(field.getType(),offset++);
            structE->attrEnv->addBinding(field.getName(),attrE);
            fieldNames.insert(field.getName());
        }
		fieldNames.clear();
        structNames.insert(typeDecl->name);
		structTLE.addBinding(typeDecl->name,structE);    
	}
}

/*
Validate that all the globals have unique names
*/
//TODO: change it to accept a reference to a list of typedecls
void validate_decls(std::vector<std::shared_ptr<ast::Declaration>> &decls) {
	// Check that global var names are unique
	std::unordered_set<std::string> globalNames;
    std::shared_ptr<Entry> entry = nullptr;
	for (const auto& decl : decls) {
		if (globalNames.find(decl->getName()) != globalNames.end()) {
            throw TypeException(fmt::format("Duplicate declaration name found: {}", decl->getName()));
		}
		entry = std::make_shared<Entry>(decl->getType());
        globalsTLE.addBinding(decl->getName(),entry);
		globalNames.insert(decl->getName());	
	}
}

/*
Validates all the functions for the following:
1. each function's name is unique
2. unique param names for each function
3. unique local var names for each function
4. typecheck body for each function
*/
//TODO: change it to accept a reference to a list of typedecls
void validate_funcs(std::vector<std::shared_ptr<ast::Function>> &funcs) {
	// Check that function names are unique
	std::unordered_set<std::string> funcNames;
	std::unordered_set<std::string> paramNames;
	std::unordered_set<std::string> localNames;
    Env localEnv = Env(); // function scope env (locals + params)
	for(const auto& func : funcs) {
		spdlog::debug("func name = {}",func->name);
		if(funcNames.find(func->name) != funcNames.end()) {
	 		throw TypeException(fmt::format("Duplicate function name found: {}", func->name));
	 	}
		// Check param names are unique
        for (const auto& param : func->params) {
            if (paramNames.find(param.getName()) != paramNames.end()) {
                throw TypeException(fmt::format("Duplicate param name {} found in function {}", param.getName(), func->name));
            }
            paramNames.insert(param.getName());
            localEnv.addBinding(param.getName(),std::make_shared<Entry>(param.getType()));
        }
		// Check local names are unique (and that there's no overlap w/param names)
        for (const auto& local : func->locals) {
            if (localNames.find(local.getName()) != localNames.end()) {
                throw TypeException(fmt::format("Duplicate local name {} found in function {}", local.getName(), func->name));
            } else if (paramNames.find(local.getName()) != paramNames.end()) {
                throw TypeException(fmt::format("Duplicate local name {} found in function {} (clases w/param)", local.getName(), func->name));
            }
            localEnv.addBinding(local.getName(),std::make_shared<Entry>(local.getType()));
            localNames.insert(local.getName());
        }
        func->typecheck(localEnv);
		paramNames.clear();
		localNames.clear();
		funcTLE.addBinding(func->name,std::make_shared<Entry>(func->retType));
        funcNames.insert(func->name);
    }
}

