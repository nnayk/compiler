#include <iostream>

class A {
public:
    virtual ~A() {}  // Polymorphic base class
};

class B : public A {};
class C : public A {};

int main() {
    A* a = new B();  // A pointer to a base class, but pointing to a derived class object B

    // Use dynamic_cast to check if 'a' points to an object of class B
    if (B* b = dynamic_cast<B*>(a)) {
        std::cout << "'a' is pointing to an object of class B" << std::endl;
    } else {
        std::cout << "'a' is not pointing to an object of class B" << std::endl;
    }

    // Use dynamic_cast to check if 'a' points to an object of class C
    if (C* c = dynamic_cast<C*>(a)) {
        std::cout << "'a' is pointing to an object of class C" << std::endl;
    } else {
        std::cout << "'a' is not pointing to an object of class C" << std::endl;
    }

    delete a;
    return 0;
}

