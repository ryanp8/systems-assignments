#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define ARR_LENGTH 10

void print_array(int* arr, int length) {
    int i;
    printf("[ ");
    for (i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

double average(int* arr, int length) {
    double sum = 0.0;
    int i;
    for (i = 0; i < length; i++) {
        sum += arr[i];
    }
    return sum / length;
}

void copy(int* arr1, int* arr2, int arr1_length) {
    int i;
    for (i = 0; i < arr1_length; i++) {
        arr2[i] = arr1[i];
    }
}

int main() {

    int arr1[ARR_LENGTH];
    int arr2[ARR_LENGTH];
    srand(time(NULL));
    
    int i;
    for (i = 0; i < ARR_LENGTH; i++) {
        arr1[i] = rand();
    }

    printf("Array 1: \n");
    print_array(arr1, ARR_LENGTH);
    printf("\n");

    printf("Array 1 Average: \n");
    double arr1_average = average(arr1, ARR_LENGTH);
    printf("%lf \n", arr1_average);
    printf("\n");

    printf("Copy of arr1: \n");
    copy(arr1, arr2, ARR_LENGTH);
    print_array(arr2, ARR_LENGTH);
    printf("\n");


    return 0;
}