#include <stdio.h>

static void print_high(long n) {
    if (n <= 0) return;
    print_high(n / 10);
    printf("%ld\n", n % 10);
}

int main(void) {
    long number;
    printf("정수 입력> ");
    scanf("%ld", &number);
    if (number > 0) print_high(number);
    return 0;
}
