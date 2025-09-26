#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

void draw_horizontal_slide(int x, int y, int length, const char *s);
void draw_vertical_slide(int x, int y, int length, const char *s);
void draw_rectangle(int c, int r);
void move_arrow_key(int key, int *x1, int *y1, int x_b, int y_b);
void gotoxy(int x, int y);

int main(void) {
    const char *slide = "■";
    int x = 1, y = 1;
    int h_len, v_len;

    printf("슬라이드바 표시\n\n");
    printf("수평 슬라이드바의 길이(최대 70) 입력> ");
    scanf("%d", &h_len);
    if (h_len > 70) h_len = 70;
    if (h_len < 1)  h_len = 1;

    printf("수직 슬라이드바의 길이(최대 19) 입력> ");
    scanf("%d", &v_len);
    if (v_len > 19) v_len = 19;
    if (v_len < 1)  v_len = 1;

    system("cls");

    int ch;
    do {
        draw_vertical_slide(1, y, v_len, slide);
        draw_horizontal_slide(x, v_len + 3, h_len, slide);
        ch = getch();
        if (ch == 0 || ch == 224) ch = 256 + getch(); // 확장키
        move_arrow_key(ch, &x, &y, h_len, v_len);
    } while (ch != 27); // ESC

    return 0;
}

void draw_rectangle(int c, int r) {
    int i, j;
    unsigned char a = 0xA6;
    unsigned char b[7];
    for (i = 1; i < 7; i++) b[i] = 0xA0 + i;

    printf("%c%c", a, b[3]);
    for (i = 0; i < c; i++) printf("%c%c", a, b[1]);
    printf("%c%c\n", a, b[4]);

    for (i = 0; i < r; i++) {
        printf("%c%c", a, b[2]);
        for (j = 0; j < c; j++) printf("  ");
        printf("%c%c\n", a, b[2]);
    }

    printf("%c%c", a, b[6]);
    for (i = 0; i < c; i++) printf("%c%c", a, b[1]);
    printf("%c%c\n", a, b[5]);
}

void draw_horizontal_slide(int x, int y, int length, const char *s) {
    int real_length = length / 2;
    gotoxy(1, y);
    draw_rectangle(real_length + 1, 1);
    gotoxy(x + 2, y + 1);
    printf("%s", s);
    gotoxy(real_length * 2 + 2, y - 1);
    printf("%2d", x);
}

void draw_vertical_slide(int x, int y, int length, const char *s) {
    gotoxy(x, 1);
    draw_rectangle(1, length);
    gotoxy(x + 2, y + 1);
    printf("%s", s);
    gotoxy(x + 6, length + 1);
    printf("%2d", y);
}

void move_arrow_key(int key, int *x1, int *y1, int x_b, int y_b) {
    switch (key) {
        case 256 + 72: // 위
            (*y1)--;
            if (*y1 < 1) *y1 = 1;
            break;
        case 256 + 75: // 왼쪽
            (*x1)--;
            if (*x1 < 1) *x1 = 1;
            break;
        case 256 + 77: // 오른쪽
            (*x1)++;
            if (*x1 > x_b) *x1 = x_b;
            break;
        case 256 + 80: // 아래
            (*y1)++;
            if (*y1 > y_b) *y1 = y_b;
            break;
        default:
            break;
    }
}

void gotoxy(int x, int y) {
    COORD Pos = { (SHORT)(x - 1), (SHORT)(y - 1) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
