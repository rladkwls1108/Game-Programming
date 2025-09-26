#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define W 10
#define H 20

static void hide_cursor(int hide){
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ci; ci.dwSize = 20; ci.bVisible = hide ? FALSE : TRUE;
    SetConsoleCursorInfo(h, &ci);
}
static void gotoxy(int x, int y){
    COORD c = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
static void set_title(const char* s){
    SetConsoleTitleA(s);
}
static void sleep_ms(int ms){
    Sleep(ms);
}

static const char SHAPES[7][4][4][4] = {
{ { {0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0} },
  { {0,0,1,0},{0,0,1,0},{0,0,1,0},{0,0,1,0} },
  { {0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0} },
  { {0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0} } },
{ { {0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0} },
  { {0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0} },
  { {0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0} },
  { {0,1,1,0},{0,1,1,0},{0,0,0,0},{0,0,0,0} } },
{ { {0,1,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0} },
  { {0,1,0,0},{0,1,1,0},{0,1,0,0},{0,0,0,0} },
  { {0,0,0,0},{1,1,1,0},{0,1,0,0},{0,0,0,0} },
  { {0,1,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0} } },
{ { {0,1,1,0},{1,1,0,0},{0,0,0,0},{0,0,0,0} },
  { {0,1,0,0},{0,1,1,0},{0,0,1,0},{0,0,0,0} },
  { {0,0,0,0},{0,1,1,0},{1,1,0,0},{0,0,0,0} },
  { {1,0,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0} } },
{ { {1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0} },
  { {0,0,1,0},{0,1,1,0},{0,1,0,0},{0,0,0,0} },
  { {0,0,0,0},{1,1,0,0},{0,1,1,0},{0,0,0,0} },
  { {0,1,0,0},{1,1,0,0},{1,0,0,0},{0,0,0,0} } },
{ { {1,0,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0} },
  { {0,1,1,0},{0,1,0,0},{0,1,0,0},{0,0,0,0} },
  { {0,0,0,0},{1,1,1,0},{0,0,1,0},{0,0,0,0} },
  { {0,1,0,0},{0,1,0,0},{1,1,0,0},{0,0,0,0} } },
{ { {0,0,1,0},{1,1,1,0},{0,0,0,0},{0,0,0,0} },
  { {0,1,0,0},{0,1,0,0},{0,1,1,0},{0,0,0,0} },
  { {0,0,0,0},{1,1,1,0},{1,0,0,0},{0,0,0,0} },
  { {1,1,0,0},{0,1,0,0},{0,1,0,0},{0,0,0,0} } }
};

static int board[H][W];

typedef struct {
    int type;
    int rot;
    int x, y;
} Piece;

static Piece cur, nxt;
static int score = 0, level = 1, lines_cleared = 0;
static int game_over = 0;

static int rnd7(){ return rand() % 7; }

static int collide(Piece p){
    for(int r=0;r<4;r++){
        for(int c=0;c<4;c++){
            if(!SHAPES[p.type][p.rot][r][c]) continue;
            int bx = p.x + c;
            int by = p.y + r;
            if (bx < 0 || bx >= W || by >= H) return 1;
            if (by >= 0 && board[by][bx]) return 1;
        }
    }
    return 0;
}

static void lock_piece(Piece p){
    for(int r=0;r<4;r++){
        for(int c=0;c<4;c++){
            if(!SHAPES[p.type][p.rot][r][c]) continue;
            int bx = p.x + c;
            int by = p.y + r;
            if (by >= 0 && by < H && bx >=0 && bx < W)
                board[by][bx] = p.type + 1;
        }
    }
}

static int clear_lines(void){
    int cleared = 0;
    for(int y=H-1;y>=0;){
        int full = 1;
        for(int x=0;x<W;x++) if(!board[y][x]) { full=0; break; }
        if(full){
            cleared++;
            for(int k=y;k>0;k--)
                for(int x=0;x<W;x++) board[k][x] = board[k-1][x];
            for(int x=0;x<W;x++) board[0][x] = 0;
        }else{
            y--;
        }
    }
    return cleared;
}

static void spawn_piece(void){
    cur = (Piece){ .type = nxt.type, .rot = 0, .x = 3, .y = -1 };
    nxt.type = rnd7();
    if (collide(cur)) game_over = 1;
}

static void add_score(int lines){
    static const int base[5] = {0,100,300,500,800};
    score += base[lines] * level;
    lines_cleared += lines;
    level = 1 + lines_cleared / 10;
}

static void draw_board_with_piece(void){
    gotoxy(0,0);
    printf("Text Tetris  | Score:%6d  Lines:%3d  Level:%2d  (Q:Quit, P:Pause)\n", score, lines_cleared, level);
    printf("+------------+   Next:\n");
    for(int y=0;y<H;y++){
        printf("|");
        for(int x=0;x<W;x++){
            int filled = board[y][x];
            int in = 0;
            for(int r=0;r<4;r++){
                for(int c=0;c<4;c++){
                    if(!SHAPES[cur.type][cur.rot][r][c]) continue;
                    int bx = cur.x + c, by = cur.y + r;
                    if (bx==x && by==y) in = 1;
                }
            }
            if (filled || in) printf("[]");
            else              printf("  ");
        }
        printf("|\n");
    }
    printf("+------------+\n");
    for(int r=0;r<4;r++){
        gotoxy(16, 2 + r);
        for(int c=0;c<4;c++){
            printf(SHAPES[nxt.type][0][r][c] ? "[]" : "  ");
        }
    }
}

static void draw_game_over(void){
    gotoxy(0, H+3);
    printf("=== GAME OVER ===   Final Score: %d   Lines: %d   Level: %d\n", score, lines_cleared, level);
    printf("Press any key to exit...");
}

static int read_key_nonblock(void){
    if (_kbhit()){
        int ch = _getch();
        if (ch == 0 || ch == 224) {
            int a = _getch();
            return 256 + a;
        }
        return ch;
    }
    return 0;
}

static int gravity_interval_ms(void){
    int base = 600;
    int step = (level-1) * 45;
    int ms = base - step;
    if (ms < 80) ms = 80;
    return ms;
}

int main(void){
    srand((unsigned)time(NULL));
    system("cls");
    hide_cursor(1);
    set_title("Text Tetris (Console)");
    for(int y=0;y<H;y++) for(int x=0;x<W;x++) board[y][x]=0;
    nxt.type = rnd7();
    spawn_piece();
    DWORD last_fall = GetTickCount();
    while(!game_over){
        draw_board_with_piece();
        int k = read_key_nonblock();
        if (k){
            if (k=='q' || k=='Q') break;
            if (k=='p' || k=='P'){
                gotoxy(0, H+2); printf("Paused. Press P to resume...");
                do { k = read_key_nonblock(); sleep_ms(10);} while(!(k=='p'||k=='P'));
                gotoxy(0, H+2); printf("                              ");
            } else {
                Piece trial = cur;
                if (k==256+75 || k=='a' || k=='A') { trial.x -= 1; if(!collide(trial)) cur = trial; }
                if (k==256+77 || k=='d' || k=='D') { trial.x += 1; if(!collide(trial)) cur = trial; }
                if (k==256+72 || k=='w' || k=='W') { trial.rot = (trial.rot+1)&3; if(!collide(trial)) cur = trial; }
                if (k==256+80 || k=='s' || k=='S') { trial.y += 1; if(!collide(trial)) cur = trial; else {
                        lock_piece(cur);
                        int c = clear_lines(); if(c) add_score(c);
                        spawn_piece();
                        last_fall = GetTickCount();
                    }
                }
                if (k==' '){
                    trial = cur;
                    while(!collide(trial)){ cur = trial; trial.y++; }
                    lock_piece(cur);
                    int c = clear_lines(); if(c) add_score(c);
                    spawn_piece();
                    last_fall = GetTickCount();
                }
            }
        }
        DWORD now = GetTickCount();
        if (now - last_fall >= (DWORD)gravity_interval_ms()){
            Piece down = cur; down.y++;
            if (!collide(down)){
                cur = down;
            }else{
                lock_piece(cur);
                int c = clear_lines(); if(c) add_score(c);
                spawn_piece();
            }
            last_fall = now;
        }
        sleep_ms(10);
    }
    draw_board_with_piece();
    draw_game_over();
    hide_cursor(0);
    _getch();
    return 0;
}
