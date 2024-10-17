#ifndef CFG_FUNC_HPP
#define CFG_FUNC_HPP
#include "TypeDeclaration.hpp"
#include "Declaration.hpp"
#include "Bblock.hpp"
#include "Function.hpp"
class CfgFunc; // forward declare for build method
class CfgFunc {
    public:
        std::vector<ast::Declaration> params;  // Function parameters
        std::shared_ptr<ast::Type> retType;  // Return type
        std::vector<ast::Declaration> locals;  // Local declarations
        std::vector<Bblock> blocks;
        static std::shared_ptr<CfgFunc> build(ast::Function &f);
   private:
        CfgFunc(std::vector<ast::Declaration> params);//,std::shared_ptr<ast::Type> retType,
//                std::vector<ast::Declaration> locals, std::vector<Bblock> blocks);
};
#endif
