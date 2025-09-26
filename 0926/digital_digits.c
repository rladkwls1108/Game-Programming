#include <stdio.h>

void number_check(int k, int line);
void digit_print(const int dim[], int line);

const int zero[20]  = {1,1,1,1,  1,0,0,1,  1,0,0,1,  1,0,0,1,  1,1,1,1};
const int one[20]   = {0,0,1,0,  0,0,1,0,  0,0,1,0,  0,0,1,0,  0,0,1,0};
const int two[20]   = {1,1,1,1,  0,0,0,1,  1,1,1,1,  1,0,0,0,  1,1,1,1};
const int three[20] = {1,1,1,1,  0,0,0,1,  1,1,1,1,  0,0,0,1,  1,1,1,1};
const int four[20]  = {1,0,0,1,  1,0,0,1,  1,1,1,1,  0,0,0,1,  0,0,0,1};
const int five[20]  = {1,1,1,1,  1,0,0,0,  1,1,1,1,  0,0,0,1,  1,1,1,1};
const int six[20]   = {1,0,0,0,  1,0,0,0,  1,1,1,1,  1,0,0,1,  1,1,1,1};
const int seven[20] = {1,1,1,1,  0,0,0,1,  0,0,0,1,  0,0,0,1,  0,0,0,1};
const int eight[20] = {1,1,1,1,  1,0,0,1,  1,1,1,1,  1,0,0,1,  1,1,1,1};
const int nine[20]  = {1,1,1,1,  1,0,0,1,  1,1,1,1,  0,0,0,1,  0,0,0,1};

int main(void) {
    int num;
    printf("디지털 숫자 출력 (1 이상의 정수)\n정수 입력> ");
    if (scanf("%d", &num) != 1 || num < 1) return 0;

    for (int line = 0; line < 5; line++) {
        number_check(num, line);
        printf("\n");
    }
    return 0;
}

void digit_print(const int dim[], int line) {
    for (int i = line * 4; i <= line * 4 + 3; i++) {
        if (dim[i] == 1) printf("■");
        else             printf("  ");
    }
    printf("  ");
}

void number_check(int k, int line) {
    if (k >= 1) {
        number_check(k / 10, line);
        switch (k % 10) {
            case 0: digit_print(zero,  line); break;
            case 1: digit_print(one,   line); break;
            case 2: digit_print(two,   line); break;
            case 3: digit_print(three, line); break;
            case 4: digit_print(four,  line); break;
            case 5: digit_print(five,  line); break;
            case 6: digit_print(six,   line); break;
            case 7: digit_print(seven, line); break;
            case 8: digit_print(eight, line); break;
            case 9: digit_print(nine,  line); break;
        }
    }
}
