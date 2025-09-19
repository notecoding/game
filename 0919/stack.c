#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

// 스택 노드 구조체 정의
struct stack_node {
    char data;
    struct stack_node *link;
};

struct stack_node *top = NULL;  // 스택 최상단 포인터

void push(char data);
char pop(void);

int main(void) {
    int count = 0;
    char key;

    do {
        count++;
        printf("%2d 번 문자입력 >", count);
        key = getch();
        printf("%c\n", key);

        if (key != 27)  // ESC 키 입력은 스택에 추가 안 함
            push(key);

    } while (key != 27);

    printf("\n\nData pop process\n\n");

    while (top != NULL) {
        key = pop();
        printf("%c ", key);
    }
    printf("\n");

    return 0;
}


void push(char data) {
    struct stack_node *new_node;
    new_node = (struct stack_node *)malloc(sizeof(struct stack_node));
    if (new_node == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(1);
    }
    new_node->data = data;
    new_node->link = top;
    top = new_node;
}

char pop(void) {
    struct stack_node *temp;
    char data;

    if (top == NULL) {
        fprintf(stderr, "스택이 비어 있습니다.\n");
        return '\0';  // 빈 스택일 때 반환 값
    }

    data = top->data;
    temp = top;
    top = top->link;
    free(temp);

    return data;
}

