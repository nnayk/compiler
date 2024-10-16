#ifndef CFG_HPP
#define CFG_HPP
#include "TypeDeclaration.hpp"
#include "Declaration.hpp"
#include "Program.hpp"
#include "CfgFunc.hpp"

class CfgProg {
    public:
        std::vector<std::shared_ptr<ast::TypeDeclaration>> typeDecls; // Pointer to TypeDeclaration objects (global struct definitions)
        std::vector<std::shared_ptr<ast::Declaration>> globals;     // Pointer to Declaration objects (pointer to global var declarations)
        std::vector<std::shared_ptr<CfgFunc>> funcs;     // Pointer to Declaration objects (pointer to global var declarations)
        static std::shared_ptr<CfgProg> build(ast::Program &p);
    private: 
        CfgProg(std::vector<std::shared_ptr<ast::TypeDeclaration>> typeDecls,std::vector<std::shared_ptr<ast::Declaration>> globals, std::vector<std::shared_ptr<CfgFunc>> funcs ); 
};
#endif
