#ifndef RETURN_EMPTY_STATEMENT_HPP
#define RETURN_EMPTY_STATEMENT_HPP

#include "AbstractStatement.hpp"

namespace ast {

class ReturnEmptyStatement : public AbstractStatement {
public:
    // Constructor
    ReturnEmptyStatement(int lineNum);
};

} // namespace ast

#endif // RETURN_EMPTY_STATEMENT_HPP

