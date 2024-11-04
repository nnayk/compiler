struct A {
    int x;
    int y;
    bool b;
    struct A *s;
};
bool f;
int abc;

void man() {
    struct A *data;
    int y;
    y=7;
    f=true;
    data->x = 5;
    data->s->s->s->y = 5;
}

void foo(int x, bool y, struct A obj) {
    struct A *data;
    data->x = 5;
}
