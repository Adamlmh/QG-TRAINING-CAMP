#include <stdio.h>
#include <ctype.h>

// 定义栈结构
#define MAX_SIZE 100

typedef struct {
    int top;
    int items[MAX_SIZE];
} Stack;

// 栈的操作函数
void push(Stack *s, int value) {
    if (s->top == MAX_SIZE - 1) {
        printf("栈溢出\n");
        return;
    }
    s->items[++(s->top)] = value;
}

int pop(Stack *s) {
    if (s->top == -1) {
        printf("栈溢出\n");
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

// 判断运算符的优先级
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

// 将中缀表达式转换为后缀表达式
void infixToPostfix(char *infix, char *postfix) {
    Stack stack;
    stack.top = -1;

    int i = 0, j = 0;
    while (infix[i] != '\0') {
        char ch = infix[i];
        if (isdigit(ch)) {
            postfix[j++] = ch;
            // 检查是否为多位数
            while (isdigit(infix[i + 1])) {
                postfix[j++] = infix[++i];
            }
            postfix[j++] = ' '; // 添加空格作为数字之间的分隔符
        } else if (ch == '(') {
            push(&stack, ch);
        } else if (ch == ')') {
            while (!isEmpty(&stack) && peek(&stack) != '(') {
                postfix[j++] = pop(&stack);
                postfix[j++] = ' ';
            }
            pop(&stack); // 弹出左括号
        } else { // 操作符
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

// 计算后缀表达式的值
int evaluatePostfix(char *postfix) {
    Stack stack;
    stack.top = -1;

    int i = 0;
    while (postfix[i] != '\0') {
        char ch = postfix[i];
        if (isdigit(ch)) {
            int operand = 0;
            // 将多位数转换为整数
            while (isdigit(postfix[i])) {
                operand = operand * 10 + (postfix[i] - '0');
                i++;
            }
            push(&stack, operand);
        } else if (ch != ' ') { // 忽略空格
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

    printf("输入中缀表达式: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);
    printf("后缀表达式: %s\n", postfix);

    int result = evaluatePostfix(postfix);
    printf("结果: %d\n", result);

    return 0;
}
