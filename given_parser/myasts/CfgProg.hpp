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
        std::string get_llvm(); // Returns the LLVM IR for the entire program
        std::string get_asm(); // Returns the asm for the entire program
        
    private: 
        CfgProg(std::vector<std::shared_ptr<ast::TypeDeclaration>> typeDecls,std::vector<std::shared_ptr<ast::Declaration>> globals, std::vector<std::shared_ptr<CfgFunc>> funcs ); 
};

//Specialize fmt::formatter for CfgFunc
template <>
struct fmt::formatter<CfgProg> : fmt::formatter<std::string> {
   auto format(const CfgProg &cfg_prog, format_context &ctx) const ->decltype(ctx.out()) {
		auto out = fmt::format_to(ctx.out(),"TYPE DECLS:");
		for(auto typeDecl : cfg_prog.typeDecls) {
			out = fmt::format_to(out,"{}",*typeDecl);
		}
   		out = fmt::format_to(out,"\nGLOBALS:");
		for(auto global : cfg_prog.globals) {
			out = fmt::format_to(out,"{}",*global);
		}
   		out = fmt::format_to(out,"\nFUNCS:");
		for(auto func : cfg_prog.funcs) {
			out = fmt::format_to(out,"{} ",*func);
		}
		return out;
	}
};
#endif
