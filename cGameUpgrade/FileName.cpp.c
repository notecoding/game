#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

#define PHI 3.141592

// ���� �ڵ�
#define COLOR_RESET 7
#define COLOR_RED 12
#define COLOR_GREEN 10
#define COLOR_BLUE 9
#define COLOR_YELLOW 14
#define COLOR_MAGENTA 13
#define COLOR_CYAN 11
#define COLOR_WHITE 15

// ���̿����� ����
typedef struct {
    int physical;
    int emotion;
    int intellect;
    char phys_status;
    char emo_status;
    char intel_status;
    int birth_year;
    int birth_month;
    int birth_day;
} Biorhythm;

// ĳ���� ����
typedef struct {
    char name[50];
    int max_hp;
    int hp;
    int max_mp;
    int mp;
    int stamina;
    int attack;
    int magic_attack;
    int defense;
    int magic_defense;
    int crit_chance;
} Character;

// ���� Ÿ��
typedef struct {
    char name[50];
    int hp;
    int max_hp;
    int attack;
    int defense;
    int magic_defense;
    int type; // 0: ���������, 1: ���������
    int is_boss;
    int hidden_type;
} Monster;

// �Լ� ����
long total_days(int year, int month, int day);
char bio_status(int v, int mod);
void calculate_biorhythm(int byr, int bmon, int bday, Biorhythm* bio);
void apply_biorhythm_to_character(Character* player, Biorhythm* bio);
void set_color(int color);
void clear_screen();
void draw_box(int x, int y, int width, int height, int color);
void draw_ui(Character* player, Monster* enemy, Biorhythm* bio, int stage);
void draw_skill_menu(int selected, Character* player);
int battle(Character* player, Monster* enemy, Biorhythm* bio, int stage);
void npc_encounter(Character* player, Biorhythm* bio);
void gotoxy(int x, int y);
void draw_hp_bar(int x, int y, int current, int max, int width);
void draw_mp_bar(int x, int y, int current, int max, int width);
void show_intro();
void rhythm_calculator(Biorhythm* player_bio);
void change_rhythm(Character* player, Biorhythm* bio);
int get_bio_color(char status);

// Ŀ�� ��ġ �̵�
void gotoxy(int x, int y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// ���� ����
void set_color(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// ȭ�� �����
void clear_screen() {
    system("cls");
}

// �ڽ� �׸���
void draw_box(int x, int y, int width, int height, int color) {
    set_color(color);
    for (int i = 0; i < height; i++) {
        gotoxy(x, y + i);
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
                printf("#");
            else
                printf(" ");
        }
    }
    set_color(COLOR_RESET);
}

// ���̿����� ���¿� ���� ����
int get_bio_color(char status) {
    if (status == '+') return COLOR_RED;
    else if (status == '-') return COLOR_BLUE;
    else return COLOR_YELLOW;
}

// HP �� �׸���
void draw_hp_bar(int x, int y, int current, int max, int width) {
    gotoxy(x, y);
    set_color(COLOR_WHITE);
    printf("HP:[");

    int filled = (current * width) / max;
    if (current > 0 && filled == 0) filled = 1;

    for (int i = 0; i < width; i++) {
        if (i < filled) {
            set_color(COLOR_GREEN);
            printf("=");
        }
        else {
            set_color(COLOR_RED);
            printf("-");
        }
    }
    set_color(COLOR_WHITE);
    printf("]%d/%d", current, max);
    set_color(COLOR_RESET);
}

// MP �� �׸���
void draw_mp_bar(int x, int y, int current, int max, int width) {
    gotoxy(x, y);
    set_color(COLOR_WHITE);
    printf("MP:[");

    int filled = (current * width) / max;
    if (current > 0 && filled == 0) filled = 1;

    for (int i = 0; i < width; i++) {
        if (i < filled) {
            set_color(COLOR_CYAN);
            printf("=");
        }
        else {
            set_color(COLOR_BLUE);
            printf("-");
        }
    }
    set_color(COLOR_WHITE);
    printf("]%d/%d", current, max);
    set_color(COLOR_RESET);
}

// ���̿����� ���
long total_days(int year, int month, int day) {
    int months[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int i;
    long total = 0L;
    total = (year - 1) * 365L + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400;
    if (!(year % 4) && year % 100 || !(year % 400)) months[1]++;
    for (i = 0; i < month - 1; i++) total += months[i];
    total += day;
    return total;
}

char bio_status(int v, int mod) {
    char result;
    double r;
    r = sin(v * 3.141592 / (mod / 2.0));
    if (r < -0.2) result = '-';
    else if ((-0.2 <= r) && (r <= 0.2)) result = '*';
    else result = '+';
    return result;
}

void calculate_biorhythm(int byr, int bmon, int bday, Biorhythm* bio) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    long total = total_days(tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday) -
        total_days(byr, bmon, bday);

    bio->physical = total % 23;
    bio->emotion = total % 28;
    bio->intellect = total % 33;
    bio->phys_status = bio_status(bio->physical, 23);
    bio->emo_status = bio_status(bio->emotion, 28);
    bio->intel_status = bio_status(bio->intellect, 33);
    bio->birth_year = byr;
    bio->birth_month = bmon;
    bio->birth_day = bday;
}

void apply_biorhythm_to_character(Character* player, Biorhythm* bio) {
    // �⺻ ���� ����
    player->max_hp = 100;
    player->max_mp = 50;
    player->attack = 15;
    player->magic_attack = 12;
    player->defense = 10;
    player->magic_defense = 8;
    player->crit_chance = 5;
    player->stamina = 100;

    // ��ü ���� ���ʽ�
    if (bio->phys_status == '+') {
        player->max_hp += 30;        // HP +30
        player->attack += 8;        // ���ݷ� +8
    }
    else if (bio->phys_status == '*') {
        player->max_hp += 10;        // HP +10
    }
    else if (bio->phys_status == '-') {
        player->attack -= 5;        // ���ݷ� -5
    }

    // ���� ���� ���ʽ�
    if (bio->intel_status == '+') {
        player->max_mp += 30;        // MP +30
        player->magic_attack += 8;   // �������ݷ� +8
    }
    else if (bio->intel_status == '*') {
        player->max_mp += 10;        // MP +10
    }
    else if (bio->intel_status == '-') {
        player->magic_attack -= 5;        // �������ݷ� -5
    }

    // ���� ���� ���ʽ�
    if (bio->emo_status == '+') {
        player->crit_chance += 30;   // ġ��Ÿ Ȯ�� +30%
    }
    else if (bio->emo_status == '*') {
        player->crit_chance += 10;    // ġ��Ÿ Ȯ�� +10%
    }
    else if (bio->emo_status == '-') {
        player->crit_chance = 0;    // ġ��Ÿ Ȯ�� 0%
    }

    // HP/MP �ִ�ġ �ʰ� ����
    if (player->hp > player->max_hp) player->hp = player->max_hp;
    if (player->mp > player->max_mp) player->mp = player->max_mp;
}

void show_intro() {
    clear_screen();
    draw_box(5, 2, 110, 28, COLOR_CYAN);

    gotoxy(40, 4);
    set_color(COLOR_YELLOW);
    printf("?????????????????????????????????");
    gotoxy(40, 5);
    printf("?   ���̿����� RPG ����       ?");
    gotoxy(40, 6);
    printf("?????????????????????????????????");

    gotoxy(10, 9);
    set_color(COLOR_WHITE);
    printf("�� ���� �Ұ�:");
    gotoxy(10, 10);
    printf("  ����� ��������� �������� ���� ���̿������� ����ϰ�,");
    gotoxy(10, 11);
    printf("  �׿� ���� ĳ������ �ɷ�ġ�� ��ȭ�ϴ� ���� RPG �����Դϴ�.");

    gotoxy(10, 13);
    set_color(COLOR_CYAN);
    printf("�� ���̿����� �ý���:");
    gotoxy(10, 14);
    set_color(COLOR_RED);
    printf("  ��ü(+)");
    set_color(COLOR_WHITE);
    printf(": ü�� +30, ���ݷ� +8");
    gotoxy(50, 14);
    set_color(COLOR_BLUE);
    printf("  ��ü(-)");
    set_color(COLOR_WHITE);
    printf(": ���ݷ� -5");

    gotoxy(10, 15);
    set_color(COLOR_RED);
    printf("  ����(+)");
    set_color(COLOR_WHITE);
    printf(": ���� +30, �������ݷ� +8");
    gotoxy(50, 15);
    set_color(COLOR_BLUE);
    printf("  ����(-)");
    set_color(COLOR_WHITE);
    printf(": �������ݷ� -5");

    gotoxy(10, 16);
    set_color(COLOR_RED);
    printf("  ����(+)");
    set_color(COLOR_WHITE);
    printf(": ġ��Ÿ Ȯ�� +30%%");
    gotoxy(50, 16);
    set_color(COLOR_BLUE);
    printf("  ����(-)");
    set_color(COLOR_WHITE);
    printf(": ġ��Ÿ Ȯ�� 0%%");


    gotoxy(10, 18);
    set_color(COLOR_GREEN);
    printf("�� ���۹�:");
    gotoxy(10, 19);
    set_color(COLOR_WHITE);
    printf("  ����Ű: ��ų ����");
    gotoxy(10, 20);
    printf("  Z Ű: ����/����");
    gotoxy(10, 21);
    printf("  X Ű: ���� ����");
    gotoxy(10, 22);
    printf("  C Ű: Ȯ��/���");

    gotoxy(10, 24);
    set_color(COLOR_YELLOW);
    printf("�� ��:");
    gotoxy(10, 25);
    set_color(COLOR_WHITE);
    printf("  - ������ ���� ���� ��������, ������ ���� ���� ������ �����ϼ���!");
    gotoxy(10, 26);
    printf("  - '���� ����' ��ų�� ��������� �����Ͽ� ���̿������� �ٲ� �� �ֽ��ϴ�.");

    gotoxy(45, 28);
    set_color(COLOR_GREEN);
    printf("�ƹ� Ű�� ���� ����...");

    _getch();
}

void rhythm_calculator(Biorhythm* player_bio) {
    clear_screen();
    draw_box(10, 3, 100, 25, COLOR_CYAN);

    gotoxy(40, 5);
    set_color(COLOR_YELLOW);
    printf("????????????????????????????");
    gotoxy(40, 6);
    printf("?   ���̿����� ����     ?");
    gotoxy(40, 7);
    printf("????????????????????????????");

    gotoxy(15, 10);
    set_color(COLOR_WHITE);
    printf("���� ����� �������: %d�� %d�� %d��",
        player_bio->birth_year, player_bio->birth_month, player_bio->birth_day);

    gotoxy(15, 12);
    set_color(COLOR_CYAN);
    printf("������������������������������������������������������������������������������������");

    gotoxy(15, 14);
    set_color(COLOR_WHITE);
    printf("�ٸ� ��������� ���̿������� Ȯ���Ͻðڽ��ϱ�?");
    gotoxy(15, 15);
    printf("������� �Է� (��: 1995 3 20): ");

    int year, month, day;
    if (scanf("%d %d %d", &year, &month, &day) == 3) {
        Biorhythm temp_bio;
        calculate_biorhythm(year, month, day, &temp_bio);

        gotoxy(15, 17);
        set_color(COLOR_YELLOW);
        printf("??? ���̿����� ��� ???");

        gotoxy(15, 19);
        set_color(COLOR_WHITE);
        printf("��ü: ");
        set_color(get_bio_color(temp_bio.phys_status));
        printf("%c", temp_bio.phys_status);

        gotoxy(30, 19);
        set_color(COLOR_WHITE);
        printf("����: ");
        set_color(get_bio_color(temp_bio.emo_status));
        printf("%c", temp_bio.emo_status);

        gotoxy(45, 19);
        set_color(COLOR_WHITE);
        printf("����: ");
        set_color(get_bio_color(temp_bio.intel_status));
        printf("%c", temp_bio.intel_status);
    }

    gotoxy(15, 24);
    set_color(COLOR_GREEN);
    printf("C Ű�� ���� ���...");

    while (_getch() != 'c' && _getch() != 'C');
}

void change_rhythm(Character* player, Biorhythm* bio) {
    clear_screen();
    draw_box(10, 3, 100, 25, COLOR_MAGENTA);

    gotoxy(40, 5);
    set_color(COLOR_YELLOW);
    printf("????????????????????????????");
    gotoxy(40, 6);
    printf("?     ���� ���� ��ų      ?");
    gotoxy(40, 7);
    printf("????????????????????????????");

    gotoxy(15, 10);
    set_color(COLOR_WHITE);
    printf("���� �������: %d�� %d�� %d��", bio->birth_year, bio->birth_month, bio->birth_day);

    gotoxy(15, 12);
    set_color(COLOR_CYAN);
    printf("������������������������������������������������������������������������������������");

    gotoxy(15, 14);
    set_color(COLOR_YELLOW);
    printf("�� ����:");
    gotoxy(15, 15);
    set_color(COLOR_WHITE);
    printf("  ��������� 1~3�� ������ �����Ͽ� ���̿������� ������ �� �ֽ��ϴ�.");
    gotoxy(15, 16);
    printf("  ����� ���̿����뿡 ���� ������ ��� ����˴ϴ�.");

    gotoxy(15, 18);
    set_color(COLOR_GREEN);
    printf("������ �ϼ��� �Է��ϼ��� (1~3, ������ ���ŷ�): ");

    int days;
    if (scanf("%d", &days) == 1) {
        if (days < -3 || days > 3 || days == 0) {
            gotoxy(15, 28);
            set_color(COLOR_RED);
            printf("�߸��� �Է�! -3 ~ 3 ������ ���� �Է��ϼ��� (0 ����)");
            Sleep(1500);
        }
        else {
            // MP �Ҹ�
            player->mp -= 10;

            bio->birth_day += days;

            // ��¥ ����
            int months[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
            if (!(bio->birth_year % 4) && bio->birth_year % 100 || !(bio->birth_year % 400))
                months[1] = 29;

            while (bio->birth_day > months[bio->birth_month - 1]) {
                bio->birth_day -= months[bio->birth_month - 1];
                bio->birth_month++;
                if (bio->birth_month > 12) {
                    bio->birth_month = 1;
                    bio->birth_year++;
                }
            }

            while (bio->birth_day < 1) {
                bio->birth_month--;
                if (bio->birth_month < 1) {
                    bio->birth_month = 12;
                    bio->birth_year--;
                }
                bio->birth_day += months[bio->birth_month - 1];
            }

            // ���̿����� ����
            calculate_biorhythm(bio->birth_year, bio->birth_month, bio->birth_day, bio);

            // ���� �缳�� (���� HP/MP ���� ����)
            int hp_ratio = (player->hp * 100) / player->max_hp;
            int mp_ratio = (player->mp * 100) / player->max_mp;

            apply_biorhythm_to_character(player, bio);

            player->hp = (player->max_hp * hp_ratio) / 100;
            player->mp = (player->max_mp * mp_ratio) / 100;

            // ��� ǥ��
            clear_screen();
            draw_box(20, 10, 80, 8, COLOR_GREEN);
            gotoxy(25, 11);
            set_color(COLOR_YELLOW);
            printf("�� ���� �Ϸ�! (MP -10)");
            gotoxy(25, 12);
            set_color(COLOR_WHITE);
            printf("���ο� �������: %d�� %d�� %d��", bio->birth_year, bio->birth_month, bio->birth_day);
            gotoxy(25, 13);
            printf("��ü:");
            set_color(get_bio_color(bio->phys_status));
            printf("%c ", bio->phys_status);
            set_color(COLOR_WHITE);
            printf("����:");
            set_color(get_bio_color(bio->emo_status));
            printf("%c ", bio->emo_status);
            set_color(COLOR_WHITE);
            printf("����:");
            set_color(get_bio_color(bio->intel_status));
            printf("%c", bio->intel_status);
            gotoxy(25, 15);
            set_color(COLOR_GREEN);
            printf("C Ű�� ���� ���...");

            char key;
            do {
                key = _getch();
            } while (key != 'c' && key != 'C');
        }
    }
}

void draw_ui(Character* player, Monster* enemy, Biorhythm* bio, int stage) {
    clear_screen();

    // ��ü ������
    draw_box(0, 0, 120, 30, COLOR_WHITE);

    // �������� ����
    gotoxy(52, 2);
    set_color(COLOR_YELLOW);
    printf("??????????????????");
    gotoxy(52, 3);
    printf("?   STAGE  %d    ?", stage);
    gotoxy(52, 4);
    printf("??????????????????");

    // �÷��̾� ����
    draw_box(8, 6, 25, 10, COLOR_GREEN);

    // �÷��̾� HP/MP (�ڽ� ��)
    draw_hp_bar(9, 5, player->hp, player->max_hp, 15);
    draw_mp_bar(9, 7, player->mp, player->max_mp, 15);

    gotoxy(15, 9);
    set_color(COLOR_GREEN);
    printf("�� PLAYER ��");

    // �÷��̾� ���� (�ڽ� �Ʒ�)
    gotoxy(9, 17);
    set_color(COLOR_WHITE);
    printf("ATK:%d M.ATK:%d", player->attack, player->magic_attack);
    gotoxy(9, 18);
    printf("DEF:%d M.DEF:%d", player->defense, player->magic_defense);
    gotoxy(9, 19);
    printf("CRIT:%d%%", player->crit_chance);

    // ���̿����� (�÷��̾� �Ʒ�)
    gotoxy(9, 20);
    set_color(COLOR_WHITE);
    printf("��ü:");
    set_color(get_bio_color(bio->phys_status));
    printf("%c ", bio->phys_status);
    set_color(COLOR_WHITE);
    printf("����:");
    set_color(get_bio_color(bio->emo_status));
    printf("%c ", bio->emo_status);
    set_color(COLOR_WHITE);
    printf("����:");
    set_color(get_bio_color(bio->intel_status));
    printf("%c", bio->intel_status);

    // �� ǥ��
    if (enemy != NULL) {
        int enemy_color = COLOR_RED;
        if (enemy->is_boss) {
            enemy_color = COLOR_MAGENTA;
        }
        else if (enemy->type == 1) {
            enemy_color = COLOR_BLUE;
        }

        draw_box(85, 6, 28, 10, enemy_color);

        // �� HP (�ڽ� ��)
        draw_hp_bar(86, 5, enemy->hp, enemy->max_hp, 20);

        gotoxy(92, 9);
        set_color(enemy_color);
        if (enemy->is_boss) {
            printf("�� BOSS ��");
        }
        else {
            printf("[ ENEMY ]");
        }

        gotoxy(90, 11);
        set_color(COLOR_WHITE);
        printf("%s", enemy->name);

        // �� ���� (�ڽ� �Ʒ�)
        gotoxy(86, 17);
        set_color(COLOR_WHITE);
        printf("ATK: %d", enemy->attack);

        if (enemy->is_boss) {
            gotoxy(86, 18);
            printf("DEF: ??  M.DEF: ??");
            gotoxy(86, 19);
            set_color(COLOR_MAGENTA);
            printf("(Ÿ�� �Ҹ�!)");
        }
        else {
            gotoxy(86, 18);
            if (enemy->defense > enemy->magic_defense) {
                set_color(COLOR_RED);
                printf("DEF: %d", enemy->defense);
                set_color(COLOR_WHITE);
                printf(" (����)");
            }
            else {
                printf("DEF: %d", enemy->defense);
            }

            gotoxy(86, 19);
            if (enemy->magic_defense > enemy->defense) {
                set_color(COLOR_BLUE);
                printf("M.DEF: %d", enemy->magic_defense);
                set_color(COLOR_WHITE);
                printf(" (����)");
            }
            else {
                printf("M.DEF: %d", enemy->magic_defense);
            }
        }
    }

    set_color(COLOR_RESET);
}

void draw_skill_menu(int selected, Character* player) {
    // �ϴ� ��ų �޴� (2x2 ��ġ)
    draw_box(2, 22, 116, 7, COLOR_BLUE);

    gotoxy(45, 23);
    set_color(COLOR_YELLOW);
    printf("=== ��ų ���� ===");
    gotoxy(30, 24);
    set_color(COLOR_WHITE);
    printf("(����Ű: �̵� | Z: ���� | C: ���̿����� ���� | X: ����)");

    char* skills[] = {
        "���� ����",
        "���� ����",
        "���� ����",
        "ȸ��"
    };

    char* skill_desc[] = {
        "0 MP - �⺻ ���� ����",
        "10 MP - ������� ����",
        "0 MP - ���� ����",
        "20 MP - HP 30 ȸ��"
    };

    int positions[4][2] = {
        {10, 26},  // �»�
        {65, 26},  // ���
        {10, 27},  // ����
        {65, 27}   // ����
    };

    for (int i = 0; i < 4; i++) {
        gotoxy(positions[i][0], positions[i][1]);

        if (i == selected) {
            set_color(COLOR_GREEN);
            printf("�� ");
        }
        else {
            set_color(COLOR_RESET);
            printf("  ");
        }

        set_color(COLOR_YELLOW);
        printf("%-12s", skills[i]);
        set_color(COLOR_CYAN);
        printf(" %s", skill_desc[i]);
    }
    set_color(COLOR_RESET);
}

int battle(Character* player, Monster* enemy, Biorhythm* bio, int stage) {
    int selected = 0;

    while (player->hp > 0 && enemy->hp > 0) {
        draw_ui(player, enemy, bio, stage);
        draw_skill_menu(selected, player);

        char key = _getch();

        if (key == 'c' || key == 'C') {
            // ���̿����� ���� ����
            rhythm_calculator(bio);
            continue;
        }
        else if (key == 'x' || key == 'X') {
            gotoxy(45, 14);
            set_color(COLOR_RED);
            printf("������ �����Ͻðڽ��ϱ�? (Y/N)");
            char confirm = _getch();
            if (confirm == 'y' || confirm == 'Y') {
                clear_screen();
                printf("\n������ �����մϴ�.\n");
                exit(0);
            }
        }
        else if (key == 72) { // ��
            selected = (selected - 2 + 4) % 4;
        }
        else if (key == 80) { // �Ʒ�
            selected = (selected + 2) % 4;
        }
        else if (key == 75) { // ����
            if (selected % 2 == 1) selected--;
        }
        else if (key == 77) { // ������
            if (selected % 2 == 0) selected++;
        }
        else if (key == 'z' || key == 'Z') {
            // ���� ������ ���� �߿��� ���� (�� ���� ����)
            if (selected == 1) {
                change_rhythm(player, bio);

                // ���� ���� �� �� ����
                if (enemy->hp > 0) {
                    int enemy_damage = enemy->attack - player->defense / 2;
                    if (enemy_damage < 1) enemy_damage = 1;
                    player->hp -= enemy_damage;

                    draw_ui(player, enemy, bio, stage);
                    gotoxy(40, 15);
                    set_color(COLOR_RED);
                    printf("%s�� �ݰ�! %d ������!", enemy->name, enemy_damage);
                    Sleep(1200);
                }
                continue;
            }

            // �÷��̾� ����
            int damage = 0;
            int mp_cost = 0;
            char message[100] = "";

            // ������ ���� ����
            int actual_def = enemy->defense;
            int actual_mdef = enemy->magic_defense;

            if (enemy->is_boss) {
                if (enemy->hidden_type == 0) { // ���������
                    actual_def = 30;
                    actual_mdef = 8;
                }
                else { // ���������
                    actual_def = 8;
                    actual_mdef = 30;
                }
            }

            switch (selected) {
            case 0: // ���� ����
                damage = player->attack - actual_def / 2;
                if (damage < 1) damage = 1;

                // ũ��Ƽ�� ����
                if (rand() % 100 < player->crit_chance) {
                    damage *= 2;
                    sprintf(message, "ũ��Ƽ��! ���� ����! %d ������!", damage);
                }
                else {
                    sprintf(message, "���� ����! %d ������!", damage);
                }
                enemy->hp -= damage;
                break;

            case 2: // ���� ����
                damage = player->magic_attack - actual_mdef / 2;
                if (damage < 1) damage = 1;
                sprintf(message, "���� ����! %d ������!", damage);
                enemy->hp -= damage;
                break;

            case 3: // ȸ��
                mp_cost = 20;
                if (player->mp >= mp_cost) {
                    int heal = 30;
                    player->hp += heal;
                    if (player->hp > player->max_hp) player->hp = player->max_hp;
                    sprintf(message, "ȸ��! HP +%d", heal);
                    player->mp -= mp_cost;
                }
                else {
                    sprintf(message, "MP�� �����մϴ�!");
                }
                break;
            }

            draw_ui(player, enemy, bio, stage);
            gotoxy(40, 15);
            set_color(COLOR_YELLOW);
            printf("%s", message);
            Sleep(1200);

            // �� ���� (ȸ���� �ƴϰ� MP�� ������� ����)
            if (enemy->hp > 0 && selected != 3) {
                int enemy_damage = enemy->attack - player->defense / 2;
                if (enemy_damage < 1) enemy_damage = 1;
                player->hp -= enemy_damage;

                draw_ui(player, enemy, bio, stage);
                gotoxy(40, 15);
                set_color(COLOR_RED);
                printf("%s�� ����! %d ������!", enemy->name, enemy_damage);
                Sleep(1200);
            }
        }
    }

    if (player->hp <= 0) {
        return 0; // �й�
    }
    else {
        // ���� Ÿ�� ����
        if (enemy->is_boss) {
            draw_ui(player, enemy, bio, stage);
            gotoxy(35, 15);
            set_color(COLOR_MAGENTA);
            if (enemy->hidden_type == 0) {
                printf("������ ��ü: ��������� (DEF 30, M.DEF 8)");
            }
            else {
                printf("������ ��ü: ��������� (DEF 8, M.DEF 30)");
            }
            Sleep(2000);
        }
        return 1; // �¸�
    }
}

void npc_encounter(Character* player, Biorhythm* bio) {
    clear_screen();
    draw_box(20, 8, 80, 20, COLOR_CYAN);

    gotoxy(35, 10);
    set_color(COLOR_YELLOW);
    printf("????????????????????????????????????");
    gotoxy(35, 11);
    printf("?  �ź��� ������ �������ϴ�!      ?");
    gotoxy(35, 12);
    printf("????????????????????????????????????");

    gotoxy(30, 15);
    set_color(COLOR_RESET);
    printf("����: �ȳ��Ͻÿ�, �밨�� ���谡��!");

    gotoxy(30, 17);
    printf("����� ���� ����: ");
    set_color(get_bio_color(bio->emo_status));
    printf("%c", bio->emo_status);

    int item_quality = rand() % 100;
    int bonus = 0;

    if (bio->emo_status == '+') {
        bonus = 30;
        gotoxy(30, 19);
        set_color(COLOR_GREEN);
        printf("�� ���� ���°� ���� ���� �������� ���� Ȯ�� +30%%!");
    }
    else if (bio->emo_status == '*') {
        bonus = 10;
        gotoxy(30, 19);
        set_color(COLOR_YELLOW);
        printf("�� ���� ���°� �Ҿ���... ���� ������ Ȯ�� +10%%");
    }

    item_quality += bonus;

    gotoxy(30, 21);
    set_color(COLOR_MAGENTA);

    if (item_quality >= 70) {
        printf("�ڡڡ� ������ ������ ȹ���߽��ϴ�! (HP +50, MP +30)");
        player->hp += 50;
        player->mp += 30;
    }
    else if (item_quality >= 40) {
        printf("�ڡ� ��� ������ ȹ���߽��ϴ�! (HP +30, MP +20)");
        player->hp += 30;
        player->mp += 20;
    }
    else {
        printf("�� �Ϲ� ������ ȹ���߽��ϴ�. (HP +15, MP +10)");
        player->hp += 15;
        player->mp += 10;
    }

    if (player->hp > player->max_hp) player->hp = player->max_hp;
    if (player->mp > player->max_mp) player->mp = player->max_mp;

    gotoxy(30, 24);
    set_color(COLOR_GREEN);
    printf("C Ű�� ���� ���...");

    char key;
    do {
        key = _getch();
    } while (key != 'c' && key != 'C');
}

int main(void) {
    srand(time(NULL));

    // ��Ʈ�� ȭ��
    show_intro();

    Character player;
    Biorhythm bio;

    int byr, bmon, bday;

    clear_screen();
    printf("\n");
    printf("  ????????????????????????????????????????\n");
    printf("  ?     ���̿����� RPG ���� ����!       ?\n");
    printf("  ????????????????????????????????????????\n\n");

    printf("  ��������� �Է��ϼ���\n\n");

    printf("  �⵵ (��: 1990): ");
    if (scanf("%d", &byr) != 1) {
        printf("  �Է� ����! �⺻������ �����մϴ�.\n");
        byr = 1990;
    }

    printf("  �� (��: 5): ");
    if (scanf("%d", &bmon) != 1) {
        printf("  �Է� ����! �⺻������ �����մϴ�.\n");
        bmon = 1;
    }

    printf("  �� (��: 15): ");
    if (scanf("%d", &bday) != 1) {
        printf("  �Է� ����! �⺻������ �����մϴ�.\n");
        bday = 1;
    }

    calculate_biorhythm(byr, bmon, bday, &bio);
    apply_biorhythm_to_character(&player, &bio);
    strcpy(player.name, "���");
    player.hp = player.max_hp;
    player.mp = player.max_mp;

    printf("\n  ���̿����� ��� �Ϸ�!\n");
    printf("  ��ü: ");
    set_color(get_bio_color(bio.phys_status));
    printf("%c", bio.phys_status);
    set_color(COLOR_RESET);
    printf(", ����: ");
    set_color(get_bio_color(bio.emo_status));
    printf("%c", bio.emo_status);
    set_color(COLOR_RESET);
    printf(", ����: ");
    set_color(get_bio_color(bio.intel_status));
    printf("%c", bio.intel_status);
    set_color(COLOR_RESET);
    printf("\n\n  ������ �����մϴ�...\n");
    Sleep(2000);


    // Stage 1: ��������� ����
    Monster stage1_enemy = { "ö�� ���", 80, 80, 12, 20, 5, 0, 0, 0 };
    if (!battle(&player, &stage1_enemy, &bio, 1)) {
        clear_screen();
        printf("\n  Game Over!\n");
        return 0;
    }

    clear_screen();
    gotoxy(48, 15);
    set_color(COLOR_GREEN);
    printf("�� Stage 1 Ŭ����! ��");
    Sleep(2000);

    // Stage 2: ��������� ����
    Monster stage2_enemy = { "�븶����", 70, 70, 15, 5, 25, 1, 0, 0 };
    if (!battle(&player, &stage2_enemy, &bio, 2)) {
        clear_screen();
        printf("\n  Game Over!\n");
        return 0;
    }

    clear_screen();
    gotoxy(48, 15);
    set_color(COLOR_GREEN);
    printf("�� Stage 2 Ŭ����! ��");
    Sleep(2000);

    // Stage 3: NPC ����
    npc_encounter(&player, &bio);

    // Stage 4: ������
    Monster boss = { "??? BOSS ???", 150, 150, 18, 0, 0, 2, 1, rand() % 2 };

    clear_screen();
    gotoxy(45, 15);
    set_color(COLOR_MAGENTA);
    printf("�ڡڡ� BOSS ����! �ڡڡ�");
    Sleep(2000);

    if (!battle(&player, &boss, &bio, 4)) {
        clear_screen();
        printf("\n  Game Over!\n");
        return 0;
    }

    // ����
    clear_screen();
    draw_box(25, 10, 70, 15, COLOR_YELLOW);
    gotoxy(40, 12);
    set_color(COLOR_YELLOW);
    printf("??????????????????????????????");
    gotoxy(40, 13);
    printf("?  ��� �������� Ŭ����!    ?");
    gotoxy(40, 14);
    printf("??????????????????????????????");

    gotoxy(35, 17);
    set_color(COLOR_GREEN);
    printf("���� HP: %d/%d  |  ���� MP: %d/%d",
        player.hp, player.max_hp, player.mp, player.max_mp);

    gotoxy(35, 19);
    set_color(COLOR_WHITE);
    printf("���� ���̿����� - ��ü:");
    set_color(get_bio_color(bio.phys_status));
    printf("%c ", bio.phys_status);
    set_color(COLOR_WHITE);
    printf("����:");
    set_color(get_bio_color(bio.emo_status));
    printf("%c ", bio.emo_status);
    set_color(COLOR_WHITE);
    printf("����:");
    set_color(get_bio_color(bio.intel_status));
    printf("%c", bio.intel_status);

    gotoxy(45, 22);
    set_color(COLOR_MAGENTA);
    printf("�ڡڡ� �����մϴ�! �ڡڡ�");

    gotoxy(0, 30);
    set_color(COLOR_RESET);

    return 0;
}