#include <stdio.h>
#include <stdlib.h>

int globalfoo;

int tailrecursive(int n) {
    if (n <= 0) return 1;
    return tailrecursive(n - 1);
}

int add(int a, int b) {
    return a + b;
}

int domath(int x) {
    int *obj1 = malloc(12);
    int *obj2 = malloc(12);
    int *ptr1 = malloc(4);
    int *ptr2 = malloc(4);

    *(int *)((char *)obj1 + 8) = (int)ptr1;
    *(int *)((char *)obj2 + 8) = (int)ptr2;

    *obj1 = x;
    *obj2 = 3;

    *ptr1 = *obj1;
    *ptr2 = *obj2;

    int count = x;
    while (count > 0) {
        int product = (*obj1) * (*obj2);
        int mul_result = product * (*ptr1);
        int division_result = mul_result / (*obj2);
        int addition_result = add(*obj1, *obj2);
        int subtraction_result = (*obj1) - (*obj2);
        count--;
    }

    free(ptr1);
    free(ptr2);
    return 0; // Example return, real logic depends on specific behavior
}

void objinstantiation(int n) {
    while (n > 0) {
        int *obj = malloc(12);
        free(obj);
        n--;
    }
}

int ackermann(int m, int n) {
    if (m == 0) return n + 1;
    if (n == 0) return ackermann(m - 1, 1);
    return ackermann(m - 1, ackermann(m, n - 1));
}

int main() {
    long input1, input2, input3, input4, input5, input6;

    printf("Enter six numbers:\n");
    scanf("%ld %ld %ld %ld %ld %ld", &input1, &input2, &input3, &input4, &input5, &input6);

    printf("%ld\n", tailrecursive(input1));
    printf("%ld\n", domath(input3));
    objinstantiation(input4);
    printf("%ld\n", ackermann(input5, input6));

    return 0;
}


