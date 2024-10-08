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
    std::shared_ptr<ast::BlockStatement> body=nullptr;
    for(auto &funcEl : data) {
        lineNum = funcEl["line"];
        name = funcEl["id"];
        current_function = new ast::Function(lineNum,name,{},NULL,{},nullptr);
        for(auto &param : funcEl["parameters"]) {
            lineNum = param["line"];
            name = param["id"];
            type = createType(param["type"],name,lineNum);
            current_function->params.push_back(ast::Declaration(lineNum,type,name));
        }
        for(auto &local : funcEl["declarations"]) {
            lineNum = local["line"];
            name = local["id"];
            spdlog::debug("found function local var {} on line {}",name,lineNum);
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
        current_function->body = body;
        current_function->retType = createType(funcEl["return_type"],"",body->lineNum);
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
    const std::string stmtStr = json["stmt"];
    if(false || stmtStr == "block") {
        return parse_block(json);
    } else if(stmtStr == "assign") {
        return parse_assignment(json);
    } else if(stmtStr == "print") {
        return parse_print(json);
    } else if(stmtStr == "if") {
        return parse_conditional(json);
    } else if(stmtStr=="while") {
        return parse_loop(json);
    } else if(stmtStr == "delete") {
        return parse_delete(json);
    } else if(stmtStr == "//return") {
        //return parse_//return(json);
    } else if(stmtStr == "invocation") {
        //return parse_invocation(json);
    } else {
        // raise exception
    }
    return stmt;
}

std::shared_ptr<ast::DeleteStatement> parse_delete(const nlohmann::json &json) {
    spdlog::debug("inside {}", __func__);

    // Extract line number and expression from the JSON
    int lineNum = json["line"];
    std::shared_ptr<ast::Expression> expression = parse_expr(json["exp"]);

    // Create and return a new DeleteStatement object
    return std::make_shared<ast::DeleteStatement>(lineNum, expression);
}

std::shared_ptr<ast::WhileStatement> parse_loop(const nlohmann::json &json) {
    spdlog::debug("inside {}", __func__);
    int lineNum = json["line"];
    std::shared_ptr<ast::Expression> guard = parse_expr(json["guard"]);
    std::shared_ptr<ast::Statement> body = parse_statement(json["body"]);
    return std::make_shared<ast::WhileStatement>(lineNum, guard, body);
}


std::shared_ptr<ast::ConditionalStatement> parse_conditional(const nlohmann::json &json) {
	spdlog::debug("inside {}",__func__);
    int lineNum = json["line"];
    std::shared_ptr<ast::Expression> guard = parse_expr(json["guard"]);
    std::shared_ptr<ast::Statement> thenBlock = parse_statement(json["then"]);
    std::shared_ptr<ast::Statement> elseBlock = nullptr;
    if(json.contains("else")) {
        elseBlock = parse_statement(json["else"]);
    }
    return std::make_shared<ast::ConditionalStatement>(lineNum,guard,thenBlock,elseBlock);
}

std::shared_ptr<ast::PrintStatement> parse_print(const nlohmann::json &json) {
	spdlog::debug("inside {}",__func__);
    return std::make_shared<ast::PrintStatement>(json["line"],parse_expr(json["exp"]),json["endl"]);
}
std::shared_ptr<ast::BlockStatement> parse_block(const nlohmann::json &json) {
	spdlog::debug("inside {}",__func__);
    std::vector<std::shared_ptr<ast::Statement>> stmts;
    auto block = std::make_shared<ast::BlockStatement>(-1,std::vector<std::shared_ptr<ast::Statement>>()); // line number unknown for now
	for(auto raw_stmt : json["list"]) {
        block->statements.push_back(parse_statement(raw_stmt));
    }
    block->setLineNum(block->statements.at(0)->getLineNum());
    return block;
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
        expr = std::make_shared<ast::InvocationExpression>(lineNum,json["id"].dump(),args);
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

/*
Creates and returns the type object given the type json identifier, var name,
and line number.
NOTE: var name (2nd param) is only used for struct case. 
*/
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
        type = std::make_shared<ast::StructType>(lineNum,var);
    }
    return type;
}
