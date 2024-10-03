#include "Parser.hpp"
#include "IntType.hpp"
#include "BoolType.hpp"
#include "StructType.hpp"
#include "ArrayType.hpp"
#include <iostream> //DELETE
#include "spdlog/spdlog.h" 
#include <string>
#include <memory>
#include <typeinfo>

std::vector<ast::TypeDeclaration*> parse_typeDecls(const nlohmann::json& data) {
    spdlog::info("inside parse_typeDecls()");
    std::vector<ast::TypeDeclaration*> type_declarations;
    std::vector<ast::Declaration> declarations;
    int lineNum;
    std::shared_ptr<ast::Type> type;
    std::string name;
    ast::TypeDeclaration * typeDecl;
    // Logic for populating type_declarations from json_object
    //     // Dynamically allocate TypeDeclaration objects and add them to the vector
    for(auto &structEl : data) {
        std::cout << "line = " << structEl["line"] << std::endl;    
        lineNum = structEl["line"];
        name = structEl["id"];
        std::cout << "loopdy doop" << std::endl;
        type = createType("struct",name,lineNum); 
        std::cout << "loopdy doop 2" << std::endl;
        spdlog::debug("Extracted var {} on line {}",name,lineNum);
        typeDecl = new ast::TypeDeclaration(lineNum,name,declarations); 
        for(auto &typeEl : structEl["fields"]) {
            lineNum = typeEl["line"];
            name = typeEl["id"];
            type = createType(typeEl["type"],name,lineNum);
            declarations.push_back(ast::Declaration(lineNum,type,name));
        }
        type_declarations.push_back(typeDecl);
        declarations.clear();
    }
    return type_declarations;     
}

std::vector<ast::Declaration*> parse_decls(const nlohmann::json& data) {
    spdlog::info("inside parse_decls()");
    std::vector<ast::Declaration*> declarations;
    int lineNum;
    std::shared_ptr<ast::Type> type;
    std::string name;
    // Logic for populating type_declarations from json_object
    //     // Dynamically allocate Declaration objects and add them to the vector
    for(auto &el : data) {
        std::cout << "line = " << el["line"] << std::endl;    
        lineNum = el["line"];
        name = el["id"];
        type = createType(el["type"],name,lineNum); 
        spdlog::debug("Extracted var {} on line {}",name,lineNum);
        declarations.push_back(new ast::Declaration(lineNum,type,name));
    }
    return declarations;     
}

std::vector<ast::Function*> parse_funcs(const nlohmann::json& data) {
    spdlog::info("inside parse_funcs()");
    std::vector<ast::Function*> functions;
    // Logic for populating type_functions from json_object
    //     // Dynamically allocate Function objects and add them to the vector
    for (nlohmann::json::const_iterator it = data.begin(); it != data.end(); ++it) {
        //functions.push_back(new Function(/* arguments */));
    }
    return functions;     
}

std::shared_ptr<ast::Type> createType(const std::string typeStr, const std::string var,
                                      const int lineNum) {
    spdlog::debug("typeStr={},var={},lineNum={}",typeStr,var,lineNum);
    std::shared_ptr<ast::Type> type;
    if(typeStr=="int") {
        spdlog::debug("int type");
        type = std::make_shared<ast::IntType>();
    } else if(typeStr=="bool") {
        spdlog::debug("bool type");
        type = std::make_shared<ast::BoolType>();
    } else if(typeStr=="int_array") {
        spdlog::debug("int_array type");
        type = std::make_shared<ast::ArrayType>();
    } else if(typeStr=="struct") {
        spdlog::debug("struct type");
        //TODO: change this to struct type. will need to pass in lineNum and var typeStr to this function
        type = std::make_shared<ast::StructType>(lineNum,var);
    }
    return type;
}
