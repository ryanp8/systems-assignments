#include <stdio.h>


int euler_01(int n) {
    int total = 0;
    int i;
    for (i = 0; i < n; i++) {
        if (i % 3 == 0 || i % 5 == 0) {
            total += i;
        }
    }

    return total;
}

int euler_05(int n) {

    int ret = 2520;

    int i;
    for (i = 11; i < n; i++) {
        int j = 1;
        while (ret * j % i != 0) {
            j++;
        }
        ret *= j;
    }

    return ret;
}

int euler_06(int n) {

    int sum = (n * (n + 1)) / 2;
    int square_of_sum = sum * sum;
    int sum_of_squares = 0;

    int i;

    for (i = 1; i < n + 1; i++) {
        sum_of_squares += i * i;
    }

    return square_of_sum - sum_of_squares;
}

int main() {
    int answer_01 = euler_01(1000);   
    printf("#1: %d \n", answer_01);

    int answer_05 = euler_05(20);
    printf("#5: %d \n", answer_05);

    int answer_06 = euler_06(100);
    printf("#6: %d \n", answer_06);

    return 0;
}