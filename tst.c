#include <stdio.h>

int troca(int *pa, int *pb) {
    int c = 0;

    c = *pa;
    *pa = *pb;
    *pb = c;

}

int main() {

    int a = 10, b = 20;

    troca(&a,&b);

    printf("%d, %d", a, b);

    return 0;
}