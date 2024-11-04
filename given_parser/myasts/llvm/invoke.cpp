struct A {
    int x;
};

int foo(int x,bool y) {
    return 3;
}

int main() {
    bool arg2 = false;
    int z=foo(3,arg2);
    return 0;
}
