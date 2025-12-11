#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <string.h>

#define MAX_USERS 8
#define MAX_QUEST 20
#define MAX_NAME 20

typedef struct {
    char name[MAX_NAME];
    int score;
    double total_time;
    int correct[MAX_QUEST];
    double response_time[MAX_QUEST];
} Player;

typedef enum {
    EASY = 1,
    NORMAL = 2,
    HARD = 3
} Difficulty;

// 함수 선언
void gotoxy(int x, int y);
void set_color(int color);
void display_intro(void);
void display_title(void);
void display_menu(void);
void display_rule(void);
void display_countdown(int seconds);
void game_control(Player *player, int quest_num, Difficulty diff);
void display_result(Player players[], int user_num, int quest_num);
void display_ranking(Player players[], int user_num);
void shuffle_order(int order[], int size);
char* get_flag_name(int flag);
char* get_action_name(int action);

// 함수 구현
void gotoxy(int x, int y) {
    COORD Pos;
    Pos.X = (SHORT)(x - 1);
    Pos.Y = (SHORT)(y - 1);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void set_color(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void display_intro(void) {
    int i;
    
    // 커서 숨기기
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
    
    system("cls");
    
    // 귀여운 로딩
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
    set_color(11);
    printf("                         ( •̀ ω •́ )✧\n");
    printf("                      게임 준비 중");
    for(i = 0; i < 3; i++) {
        printf(" .");
        fflush(stdout);
        Sleep(400);
    }
    Sleep(800);
    set_color(7);
    
    system("cls");
    
    // 귀여운 타이틀
    printf("\n\n\n\n\n\n\n\n");
    set_color(14);
    printf("                  ╭━━━━━━━━━━━━━━━━━━━━╮\n");
    Sleep(200);
    printf("                  ┃                    ┃\n");
    Sleep(200);
    set_color(11);
    printf("                  ┃  🚩 청기백기 🚩   ┃\n");
    Sleep(200);
    set_color(14);
    printf("                  ┃                    ┃\n");
    Sleep(200);
    printf("                  ╰━━━━━━━━━━━━━━━━━━━━╯\n");
    Sleep(600);
    set_color(7);
    
    // 깃발들
    printf("\n");
    printf("                      ");
    set_color(9);
    printf("💙");
    Sleep(300);
    printf(" ");
    set_color(15);
    printf("🤍");
    Sleep(300);
    printf(" ");
    set_color(12);
    printf("❤️\n");
    Sleep(600);
    set_color(7);
    
    // 간단한 설명
    printf("\n\n");
    printf("                  ");
    set_color(10);
    printf("반응속도 테스트 게임!\n");
    Sleep(500);
    set_color(7);
    
    printf("\n");
    printf("                  ");
    set_color(9);
    printf("청기↑ A");
    set_color(7);
    printf("  ");
    set_color(9);
    printf("청기↓ Z\n");
    Sleep(400);
    printf("                  ");
    set_color(15);
    printf("백기↑ K");
    set_color(7);
    printf("  ");
    set_color(15);
    printf("백기↓ M\n");
    Sleep(600);
    set_color(7);
    
    // 깜빡이는 시작
    printf("\n\n");
    for(i = 0; i < 4; i++) {
        printf("\r                                                    ");
        if(i % 2 == 0) {
            printf("\r                    ");
            set_color(11);
            printf("✨ Enter를 눌러주세요 ✨");
            set_color(7);
        }
        fflush(stdout);
        Sleep(500);
    }
    
    printf("\r                    ");
    set_color(11);
    printf("✨ Enter를 눌러주세요 ✨");
    set_color(7);
    fflush(stdout);
    
    // 키 입력 대기
    while(kbhit()) getch();
    getch();
    
    // 귀여운 카운트다운
    system("cls");
    printf("\n\n\n\n\n\n\n\n\n\n\n\n");
    
    set_color(14);
    printf("                        ヽ(•‿•)ノ\n");
    printf("                       시작할게요!\n\n");
    Sleep(800);
    
    set_color(10);
    printf("                          3\n");
    Sleep(700);
    printf("                          2\n");
    Sleep(700);
    printf("                          1\n");
    Sleep(700);
    
    set_color(14);
    printf("\n                        GO! ✧*｡\n");
    Sleep(800);
    set_color(7);
    
    // 커서 다시 보이기
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
    
    system("cls");
    Sleep(300);
}

void display_title(void) {
    set_color(11);
    printf("\n");
    printf("  ╔═══════════════════════════════════════════════════════════╗\n");
    printf("  ║                                                           ║\n");
    printf("  ║           ★ 청기백기 게임 2.0 ★                    ║\n");
    printf("  ║                                                           ║\n");
    printf("  ╚═══════════════════════════════════════════════════════════╝\n");
    set_color(7);
    printf("\n");
}

void display_menu(void) {
    set_color(10);
    printf("  [ 게임 특징 ]\n");
    set_color(7);
    printf("  • 최대 8명까지 참여 가능\n");
    printf("  • 3단계 난이도 선택\n");
    printf("  • 실시간 점수 및 랭킹 표시\n");
    printf("  • 컬러 UI 지원\n");
    printf("\n");
}

void display_rule(void) {
    set_color(14);
    printf("\n  ═══════════════════════════════════════════════\n");
    printf("              [ 키 조작 방법 ]\n");
    printf("  ═══════════════════════════════════════════════\n");
    set_color(7);
    printf("\n");
    set_color(9);
    printf("    청기 올려: A     ");
    set_color(15);
    printf("백기 올려: K\n");
    set_color(9);
    printf("    청기 내려: Z     ");
    set_color(15);
    printf("백기 내려: M\n");
    set_color(7);
    printf("\n");
    printf("  ※ 문제가 나오면 빠르고 정확하게 키를 누르세요!\n");
    printf("  ※ 1초 이내에 답해야 정답으로 인정됩니다.\n");
    printf("\n");
}

void display_countdown(int seconds) {
    int i;
    for(i = seconds; i > 0; i--) {
        gotoxy(35, 15);
        set_color(14);
        printf("[ %d초 후 시작 ]", i);
        set_color(7);
        Sleep(1000);
    }
    gotoxy(35, 15);
    set_color(10);
    printf("    시작!    ");
    set_color(7);
    Sleep(500);
}

void shuffle_order(int order[], int size) {
    int i, rnd, temp;
    for(i = 0; i < size * 2; i++) {
        rnd = rand() % size;
        temp = order[i % size];
        order[i % size] = order[rnd];
        order[rnd] = temp;
    }
}

char* get_flag_name(int flag) {
    static const char* flags[] = {"청기", "백기", "홍기"};
    return (char*)flags[flag];
}

char* get_action_name(int action) {
    static const char* actions[] = {"내려!", "올려!", "내리지말고", "올리지말고"};
    return (char*)actions[action];
}

void game_control(Player *player, int quest_num, Difficulty diff) {
    clock_t start, end;
    int i, flag1, action1, flag2, action2;
    char key;
    int is_complex;
    double time_limit = (diff == HARD) ? 0.8 : 1.0;
    
    system("cls");
    set_color(11);
    printf("\n\n          [ %s 님 차례입니다 ]\n", player->name);
    set_color(7);
    
    display_rule();
    
    printf("\n  준비되면 아무 키나 누르세요...");
    getch();
    
    display_countdown(3);
    
    for(i = 0; i < quest_num; i++) {
        system("cls");
        
        flag1 = rand() % 2;
        action1 = rand() % ((diff == EASY) ? 2 : 4);
        
        is_complex = (action1 > 1 && diff != EASY);
        
        if(is_complex) {
            flag2 = rand() % 2;
            action2 = rand() % 2;
        }
        
        gotoxy(10, 12);
        set_color(13);
        printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
        gotoxy(10, 13);
        set_color(14);
        printf("  문제 %d/%d: ", i+1, quest_num);
        set_color(15);
        
        if(is_complex) {
            set_color(flag1 == 0 ? 9 : 15);
            printf("%s ", get_flag_name(flag1));
            set_color(14);
            printf("%s ", get_action_name(action1));
            set_color(flag2 == 0 ? 9 : 15);
            printf("%s ", get_flag_name(flag2));
            set_color(14);
            printf("%s", get_action_name(action2));
        } else {
            set_color(flag1 == 0 ? 9 : 15);
            printf("%s ", get_flag_name(flag1));
            set_color(14);
            printf("%s", get_action_name(action1));
        }
        
        gotoxy(10, 14);
        set_color(13);
        printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
        set_color(7);
        
        start = clock();
        key = getch();
        end = clock();
        
        player->response_time[i] = (double)(end - start) / CLOCKS_PER_SEC;
        
        int is_correct = 0;
        
        if(player->response_time[i] < time_limit) {
            if(is_complex) {
                if((flag2 == 0 && action2 == 0 && key == 'z') ||
                   (flag2 == 0 && action2 == 1 && key == 'a') ||
                   (flag2 == 1 && action2 == 0 && key == 'm') ||
                   (flag2 == 1 && action2 == 1 && key == 'k')) {
                    is_correct = 1;
                }
            } else {
                if((flag1 == 0 && action1 == 0 && key == 'z') ||
                   (flag1 == 0 && action1 == 1 && key == 'a') ||
                   (flag1 == 1 && action1 == 0 && key == 'm') ||
                   (flag1 == 1 && action1 == 1 && key == 'k')) {
                    is_correct = 1;
                }
            }
        }
        
        player->correct[i] = is_correct;
        if(is_correct) {
            player->score++;
            player->total_time += player->response_time[i];
            
            gotoxy(30, 16);
            set_color(10);
            printf("★ 정답! (%.2f초) ★", player->response_time[i]);
        } else {
            gotoxy(30, 16);
            set_color(12);
            printf("✖ 오답 (%.2f초) ✖", player->response_time[i]);
        }
        set_color(7);
        
        Sleep(800);
    }
    
    system("cls");
    set_color(11);
    printf("\n\n          %s님의 게임이 끝났습니다!\n", player->name);
    set_color(7);
    printf("\n          점수: %d/%d\n", player->score, quest_num);
    printf("\n\n          다음 참가자는 아무 키나 누르세요...");
    getch();
}

void display_result(Player players[], int user_num, int quest_num) {
    int i, j;
    
    system("cls");
    set_color(11);
    printf("\n\n          ═══════════════════════════════════════\n");
    printf("                    [ 상세 결과 ]\n");
    printf("          ═══════════════════════════════════════\n\n");
    set_color(7);
    
    printf("  문제    ");
    for(i = 0; i < user_num; i++) {
        printf("%-12s", players[i].name);
    }
    printf("\n");
    printf("  ────────");
    for(i = 0; i < user_num; i++) {
        printf("────────────");
    }
    printf("\n");
    
    for(j = 0; j < quest_num; j++) {
        printf("  %2d번    ", j+1);
        for(i = 0; i < user_num; i++) {
            if(players[i].correct[j]) {
                set_color(10);
                printf("○ %.2f   ", players[i].response_time[j]);
            } else {
                set_color(12);
                printf("✗ %.2f   ", players[i].response_time[j]);
            }
            set_color(7);
        }
        printf("\n");
    }
    
    printf("\n");
    printf("  맞은수   ");
    for(i = 0; i < user_num; i++) {
        set_color(14);
        printf("%-12d", players[i].score);
    }
    set_color(7);
    printf("\n");
    
    printf("  총시간   ");
    for(i = 0; i < user_num; i++) {
        set_color(14);
        printf("%-12.2f", players[i].total_time);
    }
    set_color(7);
    printf("\n\n");
}

void display_ranking(Player players[], int user_num) {
    int i, j;
    Player temp;
    Player sorted[MAX_USERS];
    
    for(i = 0; i < user_num; i++) {
        sorted[i] = players[i];
    }
    
    for(i = 0; i < user_num - 1; i++) {
        for(j = i + 1; j < user_num; j++) {
            if(sorted[i].score < sorted[j].score || 
               (sorted[i].score == sorted[j].score && sorted[i].total_time > sorted[j].total_time)) {
                temp = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = temp;
            }
        }
    }
    
    set_color(11);
    printf("\n          ═══════════════════════════════════════\n");
    printf("                    [ 최종 순위 ]\n");
    printf("          ═══════════════════════════════════════\n\n");
    set_color(7);
    
    for(i = 0; i < user_num; i++) {
        if(i == 0) set_color(14);
        else if(i == 1) set_color(15);
        else if(i == 2) set_color(6);
        else set_color(7);
        
        printf("          %d위: %-10s  점수: %2d개  시간: %.2f초\n", 
               i+1, sorted[i].name, sorted[i].score, sorted[i].total_time);
    }
    set_color(7);
}

int main(void)
{
    int i, user_number, quest_number, difficulty;
    int order[MAX_USERS];
    Player players[MAX_USERS] = {0};
    char choice;
    
    // 콘솔 설정을 가장 먼저
    system("mode con cols=100 lines=35");
    system("chcp 65001 > nul");
    
    srand(time(NULL));
    
    // 버퍼 비우기
    while(kbhit()) getch();
    
    // 인트로 표시
    display_intro();
    
    // 버퍼 다시 비우기
    while(kbhit()) getch();
    
    do {
        system("cls");
        display_title();
        display_menu();
        
        printf("\n참가 인원수 (1-%d): ", MAX_USERS);
        scanf("%d", &user_number);
        if (user_number < 1 || user_number > MAX_USERS) {
            printf("잘못된 입력입니다!\n");
            Sleep(1500);
            continue;
        }
        
        printf("문제 개수 (1-%d): ", MAX_QUEST);
        scanf("%d", &quest_number);
        if (quest_number < 1 || quest_number > MAX_QUEST) {
            printf("잘못된 입력입니다!\n");
            Sleep(1500);
            continue;
        }
        
        printf("\n난이도 선택\n");
        printf("1. 쉬움 (단일 명령)\n");
        printf("2. 보통 (복합 명령 포함)\n");
        printf("3. 어려움 (3개 깃발 + 빠른 속도)\n");
        printf("선택: ");
        scanf("%d", &difficulty);
        if (difficulty < 1 || difficulty > 3) difficulty = NORMAL;
        
        for(i = 0; i < user_number; i++) {
            printf("\n%d번 참가자 이름: ", i+1);
            scanf("%s", players[i].name);
            order[i] = i;
        }
        
        printf("\n게임 순서를 섞는 중");
        for(i = 0; i < 3; i++) {
            printf(".");
            Sleep(300);
        }
        shuffle_order(order, user_number);
        
        printf("\n\n게임 순서:\n");
        set_color(14);
        for(i = 0; i < user_number; i++) {
            printf("  %d번: %s\n", i+1, players[order[i]].name);
        }
        set_color(7);
        
        printf("\n준비되면 아무 키나 누르세요...");
        getch();
        
        for(i = 0; i < user_number; i++) {
            game_control(&players[order[i]], quest_number, (Difficulty)difficulty);
        }
        
        system("cls");
        set_color(11);
        printf("\n\n          ★ 모든 게임이 끝났습니다! ★\n\n");
        set_color(7);
        printf("결과를 확인하려면 아무 키나 누르세요...");
        getch();
        
        display_result(players, user_number, quest_number);
        display_ranking(players, user_number);
        
        printf("\n\n다시 하시겠습니까? (y/n): ");
        scanf(" %c", &choice);
        
    } while(choice == 'y' || choice == 'Y');
    
    system("cls");
    set_color(14);
    printf("\n\n          게임을 종료합니다. 감사합니다!\n\n");
    set_color(7);
    Sleep(2000);
    
    return 0;
}