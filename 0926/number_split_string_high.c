#include <stdio.h>
#include <string.h>

int main(void) {
    char number[64];
    printf("금액(숫자)을 입력하고 Enter> ");
    scanf("%63s", number);

    int length = (int)strlen(number);
    for (int i = 0; i < length; i++) {
        printf("%c\n", number[i]);
    }
    return 0;
}
