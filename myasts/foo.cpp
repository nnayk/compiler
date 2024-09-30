#include "AbstractExpression.hpp"
#include "BinaryExpression.hpp"
#include "Declaration.hpp"
#include <iostream>

class DummyExpression : public ast::Expression {};

int main()
{
    ast::AbstractExpression a(1);
    std::cout << "line num = " << a.getLineNum() << std::endl;
    std::shared_ptr<ast::Expression> guard = std::make_shared<DummyExpression>();
    std::shared_ptr<ast::BinaryExpression> sum = ast::BinaryExpression::create(3,"+",guard,guard);
    std::cout << "line = " << sum->getLineNum() << std::endl;
    if(sum->getOperator() == ast::BinaryExpression::Operator::OR) return 5;
    //ast::Declaration d(3,);
    return 0;
}
