#include <stdio.h>

int main() {

    unsigned int ui = -10;
    printf("%10d\n", ui);
    printf("%u\n", ui);

    double d = 10.192439;
    printf("%10.5lf\n", d);
    printf("%-10lf\n", d);

    char a = 65;
    printf("%-10c %d\n", a, a);


    return 0;
}