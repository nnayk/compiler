#include <memory>
#include <iostream>

class Foo {
public:
    int *x;
};

int main()
{
    std::unique_ptr<Foo> ptr;
    std::cout << ptr->x << std::endl;
    return 1;
}
