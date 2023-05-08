#include <stdio.h>

int main(void) {
    printf("Hello, World!\n");

    int sum = 0;
    int i = 1;
    while(i < 200) {
        if(i % 2 == 0) {
            sum = sum + i;
        }
        i++;
    }

    printf("%d\n", sum);

    return 0;
}