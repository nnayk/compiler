#include <unordered_map>
#include <string>
#include <iostream>

class Foo {
public:
    Foo() {}
    void foo() const {
        const std::unordered_map<std::string,int> data;
        data["ab"]=4;
        std::cout << data.at("ab") << "\n";
    }
};

int main() {
    Foo f = Foo();
    f.foo();
}
