#include <stdlib.h>
struct A {
    int x;
    int y;
    struct A *s;
};

struct B {
    int qr;
    int y;
    struct A s;
};

struct B *b;

int main() {
    struct A *data = malloc(sizeof(struct A));
    data->x = 5;
    return data->x;
}
