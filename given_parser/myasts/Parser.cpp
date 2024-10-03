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
        lineNum = structEl["line"];
        name = structEl["id"];
        type = createType("struct",name,lineNum); 
        typeDecl = new ast::TypeDeclaration(lineNum,name,{}); 
        for(auto &typeEl : structEl["fields"]) {
            lineNum = typeEl["line"];
            spdlog::debug("field on lineNum {}", lineNum);
            name = typeEl["id"];
            type = createType(typeEl["type"],name,lineNum);
            declarations.push_back(ast::Declaration(lineNum,type,name));
        }
        typeDecl->fields=declarations;
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
        lineNum = el["line"];
        name = el["id"];
        type = createType(el["type"],name,lineNum); 
        declarations.push_back(new ast::Declaration(lineNum,type,name));
    }
    return declarations;     
}

std::vector<ast::Function*> parse_funcs(const nlohmann::json& data) {
    spdlog::info("inside parse_funcs()");
    int lineNum;
    std::string name;
    std::string retType;
    std::vector<ast::Function*> functions;
    ast::Function* current_function;
    std::shared_ptr<ast::Type> type;
    for(auto &funcEl : data) {
        lineNum = funcEl["line"];
        name = funcEl["id"];
        type = createType("function",name,lineNum); 
        //typeDecl = new ast::TypeDeclaration(lineNum,name,{});
        current_function = new ast::Function(lineNum,name,{},NULL,{},NULL);
        for(auto &param : funcEl["parameters"]) {
            lineNum = param["line"];
            name = param["id"];
            type = createType(param["type"],name,lineNum);
            current_function->params.push_back(ast::Declaration(lineNum,type,name));
        }
        /*
		typeDecl->fields=declarations;
        type_declarations.push_back(typeDecl);
        declarations.clear();
        */
        functions.push_back(current_function);
    }
    return functions;     
}

std::shared_ptr<ast::Type> createType(const std::string typeStr, const std::string var,
                                      const int lineNum) {
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
