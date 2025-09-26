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

    {{{0,0,0,0},{1,1,0,0},{0,1,1,0료\n");
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
        for 다");
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


