#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_LENGTH 10

int main() {

    int arr_1[ARRAY_LENGTH];
    arr_1[0] = 0;
    
    int i;
    srand(time(NULL));
    for (i = 1; i < ARRAY_LENGTH; i++) {
        int x = rand();
        arr_1[i] = x;
    }

    printf("First array:\n");
    for (i = 0; i < ARRAY_LENGTH; i++) {
        printf("%d ", arr_1[i]);
    }
    printf("\n");

    int arr_2[ARRAY_LENGTH];

    int *arr_1p = arr_1;
    int *arr_2p = arr_2;

    for (i = 0; i < ARRAY_LENGTH; i++) {
        *(arr_2p + i) = *(arr_1p + ARRAY_LENGTH - 1 - i);
    }

    printf("Second Array (using *):\n");
    for (i = 0; i < ARRAY_LENGTH; i++) {
        printf("%d ", arr_2[i]);
    }
    printf("\n");

    int arr_3[ARRAY_LENGTH];
    int *arr_3p = arr_3;
    for (i = 0; i < ARRAY_LENGTH; i++) {
        arr_3p[i] = arr_1p[ARRAY_LENGTH - 1 - i];
    }

    printf("Second Array (using []):\n");
    for (i = 0; i < ARRAY_LENGTH; i++) {
        printf("%d ", arr_2[i]);
    }
    printf("\n");


    printf("\a \n");


    return 0;
}