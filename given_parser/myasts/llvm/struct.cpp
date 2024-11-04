struct A {
    int x;
    int y;
    bool b;
    struct A *s;
};

struct B {
    int qr;
    int y;
    bool b;
    struct A s;
};

struct B *b;

int main() {
    struct A *data;
    data->s->s->y = 5;
    b->qr=4;
    b->b = true;
}
