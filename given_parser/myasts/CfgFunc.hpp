#ifndef CFG_FUNC_HPP
#define CFG_FUNC_HPP
#include "TypeDeclaration.hpp"
#include "Declaration.hpp"
#include "Bblock.hpp"
#include "Function.hpp"
class CfgFunc; // forward declare for build method
class CfgFunc {
    public:
		std::string name;
        std::vector<ast::Declaration> params;  // Function parameters
        std::shared_ptr<ast::Type> retType;  // Return type
        std::vector<ast::Declaration> locals;  // Local declarations
        std::vector<std::shared_ptr<Bblock>> blocks;
        static std::shared_ptr<CfgFunc> build(ast::Function &f);
		std::string display() const;
   private:
        CfgFunc(std::string name,std::vector<ast::Declaration> params);//,std::shared_ptr<ast::Type> retType,
//                std::vector<ast::Declaration> locals, std::vector<Bblock> blocks);
};

//Specialize fmt::formatter for CfgFunc
template <>
struct fmt::formatter<CfgFunc> : fmt::formatter<std::string> {
   auto format(const CfgFunc &cfg_func, format_context &ctx) const ->decltype(ctx.out()) {
       return fmt::format_to(ctx.out(),"{}",cfg_func.display());
   }
};
#endif
