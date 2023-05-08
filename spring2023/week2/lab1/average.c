#include <stdio.h>

int main(void) {
    int n = 0;
    double total = 0;
    double average;
    double x;

    while (scanf("%lf", &x) == 1) { // pay attention to %lf
        n = n + 1;
        total = total + x;
        average = total / n;

        printf("Total=%f Average=%f\n", total, average); // pay attention to %f
    }
}