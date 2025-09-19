#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

struct linked_list {
    char data;
    struct linked_list *link;
};

struct linked_list *head = NULL;

void add_node(char data);
void print_linked_list(struct linked_list *now);
void print_reverse_linked_list(struct linked_list *now);

int main(void) {
    int count = 0;
    char key;

    head = (struct linked_list *)malloc(sizeof(struct linked_list));
    head->link = NULL;

    do {
        count++;
        printf("%2d번 문자입력 >", count);
        key = getch();
        printf("%c\n", key);

        add_node(key);

    } while (key != 27); // ESC 키 입력 시 종료

    printf("\n\n");
    printf("입력된 순서 : ");
    print_linked_list(head->link);
    printf("\n");

    printf("입력의 역순 : ");
    print_reverse_linked_list(head->link);
    printf("\n");

    return 0;
}

void add_node(char data) {
    struct linked_list *new_node, *last;
    last = head;

    while (last->link != NULL)
        last = last->link;

    new_node = (struct linked_list *)malloc(sizeof(struct linked_list));
    new_node->data = data;

    new_node->link = last->link;
    last->link = new_node;
}

void print_linked_list(struct linked_list *now) {
    while (now != NULL) {
        printf("%c ", now->data);
        now = now->link;
    }
    printf("\n");
}

void print_reverse_linked_list(struct linked_list *now) {
    if (now == NULL)
        return;

    if (now->link != NULL)
        print_reverse_linked_list(now->link);

    printf("%c ", now->data);
}
