#ifndef REGISTER_HPP
#define REGISTER_HPP
#include <string>
class Register {
    public:
        std::string id;
        Register() : id(std::to_string(reg++)) {}
    private:
        static int reg;
};

#endif