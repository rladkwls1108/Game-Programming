#include <stdio.h>

static void print_low(long n) {
    if (n <= 0) return;
    printf("%ld\n", n % 10);
    if ((n / 10) > 0) print_low(n / 10);
}

int main(void) {
    long number;
    printf("정수 입력> ");
    scanf("%ld", &number);
    if (number > 0) print_low(number);
    return 0;
}
