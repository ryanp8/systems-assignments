#include "euler.h"

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

