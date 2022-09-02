#include <stdio.h>

int main() {

    char c = 65;
    int i = 2934;
    long l = 34298334;

    printf("===== Step 2 =====\n");
    printf("Hex:\n*c: %p\n*i: %p\n*l: %p\n", &c, &i, &l);
    printf("Decimal:\n*c: %lu\n*i: %lu\n*l: %lu\n", &c, &i, &l);


    char *cp = &c;
    int *ip = &i;
    long *lp = &l;

    printf("===== Step 4 =====\n");
    printf("Pointer values:\ncp: %p\nip: %p\nlp: %p\n", cp, ip, lp);

    *cp = 66;
    *ip = 144;
    *lp = 982734;

    printf("===== Step 5 =====\n");
    printf("Modified values:\n*c: %c\n*i: %d\n*l: %ld\n", *cp, *ip, *lp);

    unsigned int a = 133;
    int* ui_pointer = &a;
    char* char_pointer = &a;
    printf("===== Step 7 =====\n");
    printf("ui_pointer: %p ui_pointer points to: %d \n", ui_pointer, *ui_pointer);
    printf("char_pointer: %p char_pointer points to: %d \n", char_pointer, *char_pointer);

    printf("===== Step 8 =====\n");
    printf("decimal: %u\thex: %x \n", a, a);

    printf("===== Step 9 =====\n");
    int j;
    for (j = 0; j < 4; j++) {
        printf("Decimal:%hhu Hex:%hhx\n", *(char_pointer + j), *(char_pointer + j));
    }


    printf("===== Step 10 =====\n");

    for (j = 0; j < 4; j++) {
        (*(char_pointer + j))++;
        printf("decimal: %u\thex:%x \n", *ui_pointer, *ui_pointer);
    }
    for (j = 0; j < 4; j++) {
        printf("\tdecimal:%hhu hex:%hhx\n", *(char_pointer + j), *(char_pointer + j));
    }

    a = 133;

    printf("===== Step 11 ===== \n");
    for (j = 0; j < 4; j++) {
        (*(char_pointer + j))+=16;
        printf("decimal: %u\thex:%x \n", *ui_pointer, *ui_pointer);
    }
    for (j = 0; j < 4; j++) {
        printf("\tdecimal:%hhu hex:%hhx\n", *(char_pointer + j), *(char_pointer + j));
    }


    return 0;
}