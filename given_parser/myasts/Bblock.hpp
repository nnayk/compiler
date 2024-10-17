#ifndef BBLOCK_HPP
#define BBLOCK_HPP
#include "Statement.hpp"
#include <memory>

namespace ast {
    class BlockStatement;
}
class Bblock {
    public:
        std::vector<ast::Statement> stmts;
        std::shared_ptr<Bblock> parent;
        std::vector<std::shared_ptr<Bblock>> children;
        Bblock() {}
};
#endif
