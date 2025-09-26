#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define WIDTH 10
#define HEIGHT 20

int field[HEIGHT][WIDTH];
int score = 0;
int gameOver = 0;

int tetromino[7][4][4][4] = {
    {{{0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0}},
     {{0,0,1,0},{0,0,1,0},{0,0,1,0},{0,0,1,0}},
     {{0,0,0,0},{0,0,0,0},{1,1,1,1},{0,0,0,0}},
     {{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0}}},

    {{{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}},
     {{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}},
     {{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}},
     {{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}}},

    {{{0,0,0,0},{1,1,1,0},{0,1,0,0},{0,0,0,0}},
     {{0,1,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}},
     {{0,1,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},
     {{0,1,0,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}}},

    {{{0,0,0,0},{0,1,1,0},{1,1,0,0},{0,0,0,0}},
     {{1,0,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}},
     {{0,0,0,0},{0,1,1,0},{1,1,0,0},{0,0,0,0}},
     {{1,0,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}}},

    {{{0,0,0,0},{1,1,0,0},{0,1,1,0},{0,0,0,0}},
     {{0,1,0,0},{1,1,0,0},{1,0,0,0},{0,0,0,0}},
     {{0,0,0,0},{1,1,0,0},{0,1,1,0},{0,0,0,0}},
     {{0,1,0,0},{1,1,0,0},{1,0,0,0},{0,0,0,0}}},

    {{{0,0,0,0},{1,1,1,0},{0,0,1,0},{0,0,0,0}},
     {{0,1,0,0},{0,1,0,0},{1,1,0,0},{0,0,0,0}},
     {{1,0,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},
     {{0,1,1,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}}},

    {{{0,0,0,0},{1,1,1,0},{1,0,0,0},{0,0,0,0}},
     {{1,1,0,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}},
     {{0,0,1,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}},
     {{0,1,0,0},{0,1,0,0},{0,1,1,0},{0,0,0,0}}}
};

int currentBlock;
int currentRotation;
int currentX;
int currentY;

void drawField() {
    system("cls");
    printf("Score: %d\n", score);

    printf("+");
    for (int i = 0; i < WIDTH * 2; i++) printf("-");
    printf("+\n");

    for (int y = 0; y < HEIGHT; y++) {
        printf("|");
        for (int x = 0; x < WIDTH; x++) {
            int isBlock = 0;

            // 현재 블록 표시
            for (int py = 0; py < 4; py++) {
                for (int px = 0; px < 4; px++) {
                    if (tetromino[currentBlock][currentRotation][py][px]) {
                        int fx = currentX + px;
                        int fy = currentY + py;
                        if (fx == x && fy == y) {
                            isBlock = 1;
                        }
                    }
                }
            }

            if (isBlock) printf("[]");
            else if (field[y][x]) printf("[]");
            else printf("  ");
        }
        printf("|\n");
    }

    printf("+");
    for (int i = 0; i < WIDTH * 2; i++) printf("-");
    printf("+\n");

    printf("Controls: a:left d:right s:down w:rotate r:reset q:quit\n");
}

int doesCollide(int x, int y, int rotation) {
    for (int py = 0; py < 4; py++) {
        for (int px = 0; px < 4; px++) {
            if (tetromino[currentBlock][rotation][py][px]) {
                int fx = x + px;
                int fy = y + py;

                if (fx < 0 || fx >= WIDTH) return 1;
                if (fy >= HEIGHT) return 1;

                // **여기서 fy < 0 일 때는 충돌 아님 (위쪽 공간)**
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
                if (fy >= 0 && fy < HEIGHT && fx >= 0 && fx < WIDTH) {
                    field[fy][fx] = 1;
                }
            }
        }
    }
}

void clearLines() {
    for (int y = 0; y < HEIGHT; y++) {
        int full = 1;
        for (int x = 0; x < WIDTH; x++) {
            if (!field[y][x]) {
                full = 0;
                break;
            }
        }
        if (full) {
            score += 100;
            for (int ty = y; ty > 0; ty--) {
                memcpy(field[ty], field[ty-1], sizeof(field[ty]));
            }
            memset(field[0], 0, sizeof(field[0]));
        }
    }
}

void newBlock() {
    currentBlock = rand() % 7;
    currentRotation = 0;
    currentX = WIDTH / 2 - 2;
    currentY = 0;

    // 게임오버 판단: 새 블록이 시작 위치에 놓일 수 없으면 종료
    if (doesCollide(currentX, currentY, currentRotation)) {
        gameOver = 1;
    }
}

void resetGame() {
    memset(field, 0, sizeof(field));
    score = 0;
    gameOver = 0;
    newBlock();
}

void input() {
    if (_kbhit()) {
        char ch = _getch();
        if (gameOver) {
            if (ch == 'r' || ch == 'R') {
                resetGame();
            }
            if (ch == 'q' || ch == 'Q') {
                exit(0);
            }
            return;
        }

        if (ch == 'a' && !doesCollide(currentX - 1, currentY, currentRotation)) currentX--;
        else if (ch == 'd' && !doesCollide(currentX + 1, currentY, currentRotation)) currentX++;
        else if (ch == 's' && !doesCollide(currentX, currentY + 1, currentRotation)) currentY++;
        else if (ch == 'w' && !doesCollide(currentX, currentY, (currentRotation + 1) % 4)) currentRotation = (currentRotation + 1) % 4;

        if (ch == 'r' || ch == 'R') resetGame();
        if (ch == 'q' || ch == 'Q') exit(0);
    }
}

int main() {
    srand(time(NULL));
    resetGame();

int gameOverDrawn = 0;

while (1) {
    if (!gameOver) {
        drawFieldWithBorders();

        if (!doesCollide(currentX, currentY + 1, currentRotation)) {
            currentY++;
        } else {
            mergeBlock();
            clearLines();
            newBlock();
        }

        Sleep(200);
        input();
        gameOverDrawn = 0; // 게임 중이라면 다시 초기화
    } else {
        if (!gameOverDrawn) {
            drawFieldWithBorders();
            printf("\n💀 게임 오버! 💀\n");
            printf("점수: %d\n", score);
            printf("다시 시작하려면 [r], 종료하려면 [q]를 누르세요\n");
            gameOverDrawn = 1;
        }

        input();
        Sleep(100);
    }
}

    return 0;
}

