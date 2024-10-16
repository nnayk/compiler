#ifndef BBLOCK_HPP
#define BBLOCK_HPP
#include "BlockStatement.hpp"
#include "CfgFunc.hpp"
#include <memory>
class Bblock {
    public:
        std::vector<ast::BlockStatement> stmts;
        std::shared_ptr<Bblock> parent;
        std::vector<std::shared_ptr<Bblock>> children;
        Bblock() {}
};
#endif
