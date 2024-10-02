#include "AbstractExpression.hpp"
#include "BinaryExpression.hpp"
#include "Declaration.hpp"
#include <iostream>
#include <spdlog/spdlog.h>

class DummyExpression {
    public:
        int x;
        DummyExpression(int x) :
            x(x){}
};

// Overload << operator
 std::ostream& operator<<(std::ostream& os, const DummyExpression& decl) {
     os << "x = " << decl.x;
     return os;
 }

// Specialize fmt::formatter for DummyExpression
template <>
struct fmt::formatter<DummyExpression> : fmt::formatter<std::string> {
     auto format(const DummyExpression decl, format_context &ctx) const ->decltype(ctx.out()) {
             return format_to(ctx.out(), "[DummyExpression(x = {})]", decl.x);
                 }
};


int main()
{
    int x=5;
    DummyExpression exp = DummyExpression{x};
    std::cout << exp << std::endl;
    spdlog::info("DummyExpr: {}\n",exp);
}


