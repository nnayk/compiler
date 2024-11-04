#include <iostream>

int simple(int a, int b) {
    return a+b;
}

int compare() {
    int x,y;
    x=3;
    if(x>y) return 19;
    else return 34;
}

int main(int argc, char *argv[]) {
    return compare();
    //return simple(5,3);
}
