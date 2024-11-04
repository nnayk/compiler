#include <stdio.h>
#include <stdlib.h>

int varG=97;
struct cont {
    int x;
    int y;
    int yoruba;
    struct cont *abc;
};

int foo() {
    int var;
    var = 3;
    varG = 56;
    return varG;
}

int main() {
    struct cont *obj ;
    obj = malloc(sizeof(struct cont));
    obj->y = 3;
    printf("y=%d\n",obj->y);
    return obj->y;
    //return foo();
}
