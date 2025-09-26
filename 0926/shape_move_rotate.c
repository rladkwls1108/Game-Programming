#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

void rotation_right(int m[][3]);
void move_control(int m[][3]);
void print_shape(int m[][3]);
void move_shape(int m[][3]);
void print_direction(void);
void gotoxy(int x, int y);

int x = 35, y = 12; // 콘솔 위치
int inx = 0, iny = 0;

int main(void) {
    int shape[3][3] = {
        {0,1,0},
        {0,1,0},
        {1,1,1}
    };
    move_control(shape);
    return 0;
}

void rotation_right(int m[][3]) {
    int temp[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            temp[j][2 - i] = m[i][j];

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            m[i][j] = temp[i][j];
}

void print_direction(void) {
    gotoxy(25, 1);
    printf("화살표: 이동, Space: 회전, ESC: 종료");
}

void move_control(int m[][3]) {
    int key;
    do {
        while (!_kbhit()) {
            system("cls");
            move_shape(m);
        }
        key = getch();
        if (key == 0 || key == 224) key = 256 + getch(); // 확장키

        switch (key) {
            case ' ': // 스페이스
                rotation_right(m);
                move_shape(m);
                break;
            case 256 + 72: inx = 0;  iny = -1; move_shape(m); break; // ↑
            case 256 + 75: inx = -1; iny = 0;  move_shape(m); break; // ←
            case 256 + 77: inx = 1;  iny = 0;  move_shape(m); break; // →
            case 256 + 80: inx = 0;  iny = 1;  move_shape(m); break; // ↓
            default: break;
        }
    } while (key != 27); // ESC
    printf("\n");
}

void print_shape(int m[][3]) {
    for (int i = 0; i < 3; i++) {
        gotoxy(x, y + i);
        for (int j = 0; j < 3; j++) {
            if (m[i][j] == 1) printf("□");
            else              printf("  ");
        }
        printf("\n");
    }
}

void move_shape(int m[][3]) {
    do {
        system("cls");
        print_shape(m);
        print_direction();
        x += inx;
        y += iny;
        if (y > 23) y = 23;
        else if (y < 2) y = 2;
        if (x > 75) x = 75;
        else if (x < 1) x = 1;
        Sleep(100);
    } while (!_kbhit());
}

void gotoxy(int x, int y) {
    COORD Pos = { (SHORT)(x - 1), (SHORT)(y - 1) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
