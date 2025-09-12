#include <stdio.h>
#include <conio.h>
#include <windows.h>
#define X_MAX 79
#define Y_MAX 24

void move_arrow_key(char chr, int *x, int *y, int x_b, int y_b);
void gotoxy(int x, int y);

int main(void) {
    char key;
    int x=10, y=5;
    do {
        gotoxy(x, y);
        printf("A");
        key=getch();
        move_arrow_key(key, &x, &y, X_MAX, Y_MAX);
    } while(key!=27); // ESC 종료
    return 0;
}

void move_arrow_key(char key, int *x1, int *y1, int x_b, int y_b) {
    switch(key) {
        case 72: *y1=*y1-1; if (*y1<1) *y1=1; break;        // ↑
        case 75: *x1=*x1-1; if (*x1<1) *x1=1; break;        // ←
        case 77: *x1=*x1+1; if (*x1>x_b) *x1=x_b; break;    // →
        case 80: *y1=*y1+1; if (*y1>y_b) *y1=y_b; break;    // ↓
        default: return;
    }
}

void gotoxy(int x, int y) {
    COORD Pos = {x - 1, y - 1};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

