#include <stdio.h>
#include <math.h>

static void serial_number(long number) {
    if (number <= 0) return;
    int length = (int)(log10((double)number)) + 1;
    for (int i = length; i >= 1; i--) {
        long base = (long)pow(10.0, i - 1);
        long digit = number / base;
        printf("%ld\n", digit);
        number -= digit * base;
    }
}

int main(void) {
    long number;
    printf("정수 입력> ");
    scanf("%ld", &number);
    serial_number(number);
    return 0;
}
