#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define WIDTH 10
#define HEIGHT 20

int field[HEIGHT][WIDTH] = {0};
int score = 0;
int gameOver = 0;

int tetromino[7][4][4][4] = {
    // I
    {{{0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0}},
     {{0,0,1,0},{0,0,1,0},{0,0,1,0},{0,0,1,0}},
     {{0,0,0,0},{0,0,0,0},{1,1,1,1},{0,0,0,0}},
     {{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0}}},

    // O
    {{{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}},
     {{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}},
     {{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}},
     {{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}}},

    // T
    {{{0,0,0,0},{1,1,1,0},{0,1,0,0},{0,0,0,0}},
     {{0,1,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}},
     {{0,1,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},
     {{0,1,0,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}}},

    // S
    {{{0,0,0,0},{0,1,1,0},{1,1,0,0},{0,0,0,0}},
     {{1,0,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}},
     {{0,0,0,0},{0,1,1,0},{1,1,0,0},{0,0,0,0}},
     {{1,0,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}}},

    // Z
    {{{0,0,0,0},{1,1,0,0},{0,1,1,0},{0,0,0,0}},
     {{0,1,0,0},{1,1,0,0},{1,0,0,0},{0,0,0,0}},
     {{0,0,0,0},{1,1,0,0},{0,1,1,0},{0,0,0,0}},
     {{0,1,0,0},{1,1,0,0},{1,0,0,0},{0,0,0,0}}},

    // J
    {{{0,0,0,0},{1,1,1,0},{0,0,1,0},{0,0,0,0}},
     {{0,1,0,0},{0,1,0,0},{1,1,0,0},{0,0,0,0}},
     {{1,0,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},
     {{0,1,1,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}}},

    // L
    {{{0,0,0,0},{1,1,1,0},{1,0,0,0},{0,0,0,0}},
     {{1,1,0,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}},
     {{0,0,1,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},
     {{0,1,0,0},{0,1,0,0},{0,1,1,0},{0,0,0,0}}}
};

int currentBlock, currentRotation = 0;
int currentX = 3, currentY = 0;

void drawFieldWithBorders() {
    system("cls");
    printf("Score: %d\n", score);

    // 상단 구분선
    printf("+");
    for (int i = 0; i < WIDTH * 2; i++) printf("-");
    printf("+\n");

    for (int y = 0; y < HEIGHT; y++) {
        printf("|");
        for (int x = 0; x < WIDTH; x++) {
            int isCurrentBlock = 0;

            // 현재 떨어지는 블록을 field 위에 그리기
            for (int py = 0; py < 4; py++) {
                for (int px = 0; px < 4; px++) {
                    if (tetromino[currentBlock][currentRotation][py][px]) {
                        int fx = currentX + px;
                        int fy = currentY + py;
                        if (fx == x && fy == y) {
                            isCurrentBlock = 1;
                        }
                    }
                }
            }

            if (isCurrentBlock) {
                printf("[]"); // 현재 블록
            } else if (field[y][x]) {
                printf("[]"); // 쌓인 블록
            } else {
                printf("  "); // 빈칸
            }
        }
        printf("|\n");
    }

    // 하단 구분선
    printf("+");
    for (int i = 0; i < WIDTH * 2; i++) printf("-");
    printf("+\n");

    printf("\n조작키: ← a | → d | ↓ s | 회전 w | 리셋 r | 종료 q\n");

}

int doesCollide(int x, int y, int rotation) {
    for (int py = 0; py < 4; py++) {
        for (int px = 0; px < 4; px++) {
            if (tetromino[currentBlock][rotation][py][px]) {
                int fx = x + px;
                int fy = y + py;

                // 필드 밖으로 나가면 충돌
                if (fx < 0 || fx >= WIDTH || fy >= HEIGHT) return 1;

                // 필드에 쌓인 블록과 겹치면 충돌
                if (fy >= 0 && field[fy][fx]) return 1;
            }
        }
    }
    return 0;
}


void mergeBlock() {
    for (int py = 0; py < 4; py++) {
        for (int px = 0; px < 4; px++) {
            if (tetromino[currentBlock][currentRotation][py][px]) {
                int fx = currentX + px;
                int fy = currentY + py;
                if (fy >= 0 && fy < HEIGHT && fx >= 0 && fx < WIDTH)
                    field[fy][fx] = 1;
            }
        }
    }
}

void clearLines() {
    for (int y = 0; y < HEIGHT; y++) {
        int full = 1;
        for (int x = 0; x < WIDTH; x++) {
            if (field[y][x] == 0) {
                full = 0;
                break;
            }
        }

        if (full) {
            score += 100;
            for (int ty = y; ty > 0; ty--) {
                for (int x = 0; x < WIDTH; x++) {
                    field[ty][x] = field[ty - 1][x];
                }
            }
            for (int x = 0; x < WIDTH; x++)
                field[0][x] = 0;
        }
    }
}

void newBlock() {
    currentBlock = rand() % 7;
    currentRotation = 0;
    currentX = WIDTH / 2 - 2;
    currentY = 0;

    // 생성된 블록이 시작 위치에서 이미 충돌하면 게임오버!
    if (doesCollide(currentX, currentY, currentRotation)) {
        gameOver = 1;
    }
}


void resetGame() {
    memset(field, 0, sizeof(field));
    score = 0;
    currentBlock = rand() % 7;
    currentRotation = 0;
    currentX = 3;
    currentY = 0;
    gameOver = 0;
}

void input() {
    if (_kbhit()) {
        char key = _getch();

        if (key == 'a' && !doesCollide(currentX - 1, currentY, currentRotation)) currentX--;
        if (key == 'd' && !doesCollide(currentX + 1, currentY, currentRotation)) currentX++;
        if (key == 's' && !doesCollide(currentX, currentY + 1, currentRotation)) currentY++;
        if (key == 'w' && !doesCollide(currentX, currentY, (currentRotation + 1) % 4))
            currentRotation = (currentRotation + 1) % 4;

        if (key == 'r' || key == 'R') {
            resetGame();
        }

        if (key == 'q' || key == 'Q') {
            system("cls");
            printf("👋 게임을 종료합니다.\n");
            exit(0);
        }
    }
}


int main() {
    srand(time(NULL));
    resetGame();

    while (1) {
        drawFieldWithBorders();
        Sleep(200);
        input();

        if (gameOver) {
            system("cls");
            drawFieldWithBorders();
            printf("\n💀 게임 오버! 💀\n");
            printf("점수: %d\n", score);
            printf("\n다시 시작하려면 [r], 종료하려면 [q]를 누르세요\n");

            continue; // 게임 멈춤, 키 입력만 대기
        }

        if (!doesCollide(currentX, currentY + 1, currentRotation)) {
            currentY++;
        } else {
            mergeBlock();
            clearLines();
            newBlock();
        }
    }

    return 0;
}





