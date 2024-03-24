#include <stdio.h>
#include <ctype.h>

// ����ջ�ṹ
#define MAX_SIZE 100

typedef struct {
    int top;
    int items[MAX_SIZE];
} Stack;

// ջ�Ĳ�������
void push(Stack *s, int value) {
    if (s->top == MAX_SIZE - 1) {
        printf("ջ���\n");
        return;
    }
    s->items[++(s->top)] = value;
}

int pop(Stack *s) {
    if (s->top == -1) {
        printf("ջ���\n");
        return -1;
    }
    return s->items[(s->top)--];
}

int peek(Stack *s) {
    return s->items[s->top];
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

// �ж�����������ȼ�
int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

// ����׺���ʽת��Ϊ��׺���ʽ
void infixToPostfix(char *infix, char *postfix) {
    Stack stack;
    stack.top = -1;

    int i = 0, j = 0;
    while (infix[i] != '\0') {
        char ch = infix[i];
        if (isdigit(ch)) {
            postfix[j++] = ch;
            // ����Ƿ�Ϊ��λ��
            while (isdigit(infix[i + 1])) {
                postfix[j++] = infix[++i];
            }
            postfix[j++] = ' '; // ��ӿո���Ϊ����֮��ķָ���
        } else if (ch == '(') {
            push(&stack, ch);
        } else if (ch == ')') {
            while (!isEmpty(&stack) && peek(&stack) != '(') {
                postfix[j++] = pop(&stack);
                postfix[j++] = ' ';
            }
            pop(&stack); // ����������
        } else { // ������
            while (!isEmpty(&stack) && precedence(ch) <= precedence(peek(&stack))) {
                postfix[j++] = pop(&stack);
                postfix[j++] = ' ';
            }
            push(&stack, ch);
        }
        i++;
    }

    while (!isEmpty(&stack)) {
        postfix[j++] = pop(&stack);
        postfix[j++] = ' ';
    }
    postfix[j] = '\0';
}

// �����׺���ʽ��ֵ
int evaluatePostfix(char *postfix) {
    Stack stack;
    stack.top = -1;

    int i = 0;
    while (postfix[i] != '\0') {
        char ch = postfix[i];
        if (isdigit(ch)) {
            int operand = 0;
            // ����λ��ת��Ϊ����
            while (isdigit(postfix[i])) {
                operand = operand * 10 + (postfix[i] - '0');
                i++;
            }
            push(&stack, operand);
        } else if (ch != ' ') { // ���Կո�
            int operand2 = pop(&stack);
            int operand1 = pop(&stack);
            switch (ch) {
                case '+':
                    push(&stack, operand1 + operand2);
                    break;
                case '-':
                    push(&stack, operand1 - operand2);
                    break;
                case '*':
                    push(&stack, operand1 * operand2);
                    break;
                case '/':
                    push(&stack, operand1 / operand2);
                    break;
            }
        }
        i++;
    }

    return pop(&stack);
}

int main() {
    char infix[MAX_SIZE], postfix[MAX_SIZE];

    printf("������׺���ʽ: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);
    printf("��׺���ʽ: %s\n", postfix);

    int result = evaluatePostfix(postfix);
    printf("���: %d\n", result);

    return 0;
}
