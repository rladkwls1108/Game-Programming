#include <stdio.h>

static void reverse_number(long number) {
    if (number <= 0) return;
    while (number > 0) {
        printf("%ld\n", number % 10);
        number /= 10;
    }
}

int main(void) {
    long number;
    printf("정수 입력> ");
    scanf("%ld", &number);
    reverse_number(number);
    return 0;
}
