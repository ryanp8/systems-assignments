#include <stdio.h>

#include "euler.h"

int main() {
    int answer_01 = euler_01(1000.0);   
    printf("#1: %d \n", answer_01);

    int answer_05 = euler_05(20);
    printf("#5: %d \n", answer_05);

    int answer_06 = euler_06(100);
    printf("#6: %d \n", answer_06);

    return 0;
}