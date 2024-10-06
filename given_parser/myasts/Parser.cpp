#include "Parser.hpp"
#include "IntType.hpp"
#include "BoolType.hpp"
#include "StructType.hpp"
#include "ArrayType.hpp"
#include "DotExpression.hpp"
#include "InvocationExpression.hpp"
#include "IndexExpression.hpp"
#include "UnaryExpression.hpp"
#include "BinaryExpression.hpp"
#include "IdentifierExpression.hpp"
#include "IntegerExpression.hpp"
#include "TrueExpression.hpp"
#include "FalseExpression.hpp"
#include "NewArrayExpression.hpp"
#include "NewExpression.hpp"
#include "NullExpression.hpp"

#include <iostream> //DELETE
#include <spdlog/spdlog.h> 
#include <string>
#include <memory>
#include <typeinfo>

std::vector<ast::TypeDeclaration*> parse_typeDecls(const nlohmann::json& data) {
    spdlog::info("inside parse_typeDecls()");
    std::vector<ast::TypeDeclaration*> type_declarations;
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
            typeDecl->fields.push_back(ast::Declaration(lineNum,type,name));
        }
        type_declarations.push_back(typeDecl);
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
    ast::Function* current_function; //TODO: change this to unique ptr
    std::shared_ptr<ast::Type> type;
    std::shared_ptr<ast::BlockStatement> body=NULL;;
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
        for(auto &local : funcEl["declarations"]) {
            lineNum = local["line"];
            name = local["id"];
            type = createType(local["type"],name,lineNum);
            current_function->locals.push_back(ast::Declaration(lineNum,type,name));
        }
        for(auto raw_stmt : funcEl["body"]) {
            spdlog::debug("stmt: ");
            spdlog::debug(raw_stmt["stmt"]);
            auto stmt = parse_statement(raw_stmt);  
            if(!body) {
                body = std::make_shared<ast::BlockStatement>(raw_stmt["line"],std::vector<std::shared_ptr<ast::Statement>>{stmt}); // use getLineNum()
            }
            else {
                body->statements.push_back(stmt);
            }
        }
        current_function->locals.push_back(ast::Declaration(lineNum,type,name));
        functions.push_back(current_function);
    }
    return functions;     
}
/*
 * This function parses the json for the top level statement. It creates
 * and returns a statement object with nested expressions.
*/
std::shared_ptr<ast::Statement> parse_statement(const nlohmann::json &json) {
	spdlog::debug("inside parse_statement");
	spdlog::debug("json={}",json.dump());
    std::shared_ptr<ast::Statement> stmt;
    auto stmtStr = json["stmt"];
    if(stmtStr == "block") {
        // no line number! use line number of the first nested expr
    } else if(stmtStr == "assign") {
        stmt = parse_assignment(json);
    } else if(stmtStr == "print") {
    } else if(stmtStr == "if") {
    } else if(stmtStr=="while") {
    } else if(stmtStr == "delete") {
    } else if(stmtStr == "return") {
    } else if(stmtStr == "invocation") {
    } else {
        // print stmt
        // make sure to consider println -- see benchmark.json for example structure
    }
    return stmt;
}

std::shared_ptr<ast::AssignmentStatement> parse_assignment(const nlohmann::json &json) {
	spdlog::debug("inside parse_assignment");
	int lineNum = json["line"];
	std::shared_ptr<ast::Lvalue> target = parse_lvalue(json["target"]);
    spdlog::debug("target parsed, now gonna parse source");
	std::shared_ptr<ast::Expression> source = parse_expr(json["source"]);
	return make_shared<ast::AssignmentStatement>(lineNum,target,source);	
}

std::shared_ptr<ast::Lvalue> parse_lvalue(const nlohmann::json &json) {
	spdlog::debug("inside {}",__func__);
    int lineNum = json["line"];
    spdlog::debug("line = {}",lineNum);
	if(json.contains("left")) {
        if(json.contains("index")) {
            std::shared_ptr<ast::LvalueIndex> lvalue;
            spdlog::debug("LvalueIndex");
            lvalue = std::make_shared<ast::LvalueIndex>(lineNum,nullptr,nullptr);
            lvalue->index = parse_expr(json["index"]);
            lvalue->left  = parse_lvalue(json["left"]); 
            return lvalue;
        } else {
            spdlog::debug("LvalueDot");
            std::shared_ptr<ast::LvalueDot> lvalue;
            lvalue = std::make_shared<ast::LvalueDot>(lineNum,nullptr,json["id"]);
            lvalue->left  = parse_lvalue(json["left"]); 
            return lvalue;
        }
	} else {
        std::shared_ptr<ast::LvalueId> lvalue;
        spdlog::debug("LvalueId");
        lvalue = parse_lvalueId(lineNum,json);
        return lvalue;
    }
}

/*
 * Takes in json w/an "id" key and returns an LvalueId object
*/
std::shared_ptr<ast::LvalueId> parse_lvalueId(int lineNum,const nlohmann::json &json) {
    return std::make_shared<ast::LvalueId>(lineNum,json["id"]);
}

std::shared_ptr<ast::Expression> parse_expr(const nlohmann::json &json) {
	spdlog::debug("inside {}",__func__);
    const std::string &exprStr = json["exp"];
    const int lineNum = json["line"];
    std::shared_ptr<ast::Expression> expr;
    spdlog::debug("parsing {} expr",exprStr);
    if(exprStr == "invocation") {
        std::vector<std::shared_ptr<ast::Expression>> args;
        expr = std::make_shared<ast::InvocationExpression>(lineNum,json["name"].dump(),args);
        for(auto arg:json["args"]) {
            args.push_back(parse_expr(arg));
        }
        std::dynamic_pointer_cast<ast::InvocationExpression>(expr)->arguments = args;
    } else if(exprStr == "dot") {
        expr = std::make_shared<ast::DotExpression>(lineNum,parse_expr(json["left"]),json["id"]);
    } else if(exprStr == "index") {
        expr = std::make_shared<ast::IndexExpression>(lineNum,parse_expr(json["left"]),parse_expr(json["index"]));
    } else if(exprStr == "unary") {
        expr = ast::UnaryExpression::create(lineNum,json["operator"],parse_expr(json["operand"]));
    } else if(exprStr == "binary") {
        expr = ast::BinaryExpression::create(lineNum,json["operator"],parse_expr(json["lft"]),parse_expr(json["rht"]));
    } else if(exprStr == "id") {
        expr = std::make_shared<ast::IdentifierExpression>(lineNum,json["id"]); 
    } else if(exprStr == "num") {
        expr = std::make_shared<ast::IntegerExpression>(lineNum,json["value"]);
    } else if(exprStr == "true") {
        expr = std::make_shared<ast::TrueExpression>(lineNum);
    } else if(exprStr == "false") {
        expr = std::make_shared<ast::FalseExpression>(lineNum);
    } else if(exprStr == "new") {
        // could be either a NewArrayExpr of a NewExpr, have to consider both
        // NewArrayExpr will have a size attribute, newExpr (ie a new struct
        // won't)
        if(json.contains("size")) {
            expr = std::make_shared<ast::NewArrayExpression>(lineNum,json["size"]);
        } else {
            expr = std::make_shared<ast::NewExpression>(lineNum,json["id"]);
        }
    } else if(exprStr == "null") {
            expr = std::make_shared<ast::NullExpression>(lineNum);
    }
    return expr;
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
