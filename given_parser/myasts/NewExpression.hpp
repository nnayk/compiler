#ifndef NEW_EXPRESSION_HPP
#define NEW_EXPRESSION_HPP

#include "AbstractExpression.hpp"
#include <string>

namespace ast {

class NewExpression : public AbstractExpression {
public:
    // Constructor
    NewExpression(int lineNum, const std::string& id);

    // Getter method for id
    const std::string& getId() const;
    std::string display() const override {
        auto output = fmt::format("NewExpression(lineNum={},struct={})",lineNum,id);
        output+="\n";
        return output;
    }

private:
    std::string id; // The identifier for the type being instantiated
};

} // namespace ast

#endif // NEW_EXPRESSION_HPP

