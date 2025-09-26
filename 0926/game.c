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

void draw() {
    system("cls");
    printf("Score: %d\n", score);

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (field[y][x])
                printf("[]");
            else
                printf("  ");
        }
        printf("\n");
    }

    for (int py = 0; py < 4; py++) {
        for (int px = 0; px < 4; px++) {
            if (tetromino[currentBlock][currentRotation][py][px]) {
                int fx = currentX + px;
                int fy = currentY + py;
                if (fy >= 0 && fy < HEIGHT && fx >= 0 && fx < WIDTH) {
                    COORD pos = { fx * 2, fy + 1 };
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
                    printf("[]");
                }
            }
        }
    }
}

int doesCollide(int nx, int ny, int nr) {
    for (int py = 0; py < 4; py++) {
        for (int px = 0; px < 4; px++) {
            if (tetromino[currentBlock][nr][py][px]) {
                int fx = nx + px;
                int fy = ny + py;
                if (fx < 0 || fx >= WIDTH || fy >= HEIGHT || (fy >= 0 && field[fy][fx]))
                    return 1;
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
    currentX = 3;
    currentY = 0;
    if (doesCollide(currentX, currentY, currentRotation)) {
        gameOver = 1;
    }
}

void input() {
    if (_kbhit()) {
        char key = _getch();
        if (key == 'a' && !doesCollide(currentX - 1, currentY, currentRotation)) currentX--;
        if (key == 'd' && !doesCollide(currentX + 1, currentY, currentRotation)) currentX++;
        if (key == 's' && !doesCollide(currentX, currentY + 1, currentRotation)) currentY++;
        if (key == 'w' && !doesCollide(currentX, currentY, (currentRotation + 1) % 4))
            currentRotation = (currentRotation + 1) % 4;
    }
}

int main() {
    srand(time(NULL));
    newBlock();
    while (!gameOver) {
        draw();
        Sleep(200);  // 속도 조절
        input();

        if (!doesCollide(currentX, currentY + 1, currentRotation)) {
            currentY++;
        } else {
            mergeBlock();
            clearLines();
            newBlock();
        }
    }

    system("cls");
    printf("\n\nGame Over!\nFinal Score: %d\n", score);
    system("pause");
    return 0;
}
