#include <stdio.h>
#include <stdlib.h>

// 定义队列节点结构
typedef struct Node {
    void *data;
    struct Node *next;
} Node;

// 定义队列结构
typedef struct {
    Node *front; // 队头指针
    Node *rear;  // 队尾指针
    int size;    // 队列长度
} Queue;

// 初始化队列
void initQueue(Queue *queue) {
    queue->front = queue->rear = NULL;
    queue->size = 0;
}

// 入队
void enqueue(Queue *queue, void *data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("内存分配失败了呢\n");
        exit(0);
    }
    newNode->data = data;
    newNode->next = NULL;

    if (queue->rear == NULL) { // 队列为空
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    queue->size++;
}

// 出队并返回队头元素
void *dequeue(Queue *queue) {
    if (queue->front == NULL) {
        printf("队列是空的哟\n");
        return NULL;
    }

    Node *temp = queue->front;
    void *data = temp->data;
    queue->front = temp->next;
    free(temp);

    if (queue->front == NULL) { // 队列为空
        queue->rear = NULL;
    }
    queue->size--;

    return data;
}

// 查询队列长度
int queueSize(Queue *queue) {
    return queue->size;
}

// 查看队头元素
void *peek(Queue *queue) {
    if (queue->front == NULL) {
        printf("队列是空的哟\n");
        return NULL;
    }
    return queue->front->data;
}

// 打印队列中所有元素
void printQueue(Queue *queue, void (*printData)(void *)) {
    Node *current = queue->front;
    while (current != NULL) {
        printData(current->data);
        printf(" ");
        current = current->next;
    }
    printf("\n");
}

// 判断队列是否为空
int isEmpty(Queue *queue) {
    return queue->front == NULL;
}

// 销毁队列
void destroyQueue(Queue *queue) {
    while (queue->front != NULL) {
        Node *temp = queue->front;
        queue->front = queue->front->next;
        free(temp->data);
        free(temp);
    }
    queue->rear = NULL;
    queue->size = 0;
}

// 打印字符元素
void printChar(void *data) {
    printf("%c", *((char *)data));
}

int main() {
    Queue queue;
    initQueue(&queue);
    int choice;
    do {
    printf("====================\n");
    printf("[1]\t入队\n");
    printf("[2]\t出队\n");
    printf("[3]\t查看队头\n");
    printf("[4]\t打印队列\n");
    printf("[5]\t列队长度\n");
    printf("[6]\t判空\n");
    printf("[7]\t销毁链表\n");
    printf("[8]\t退出程序\n");
    printf("====================\n");
        printf("请输入你的选择: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                    char *data = (char *)malloc(sizeof(char));
                    printf("请学长输入一个字符: ");
                    scanf(" %c", data);
                    enqueue(&queue, data);
                break;
            }
            case 2: {
                void *data = dequeue(&queue);
                if (data != NULL) {
                    printf("即将把下面这个元素从列中移除了噢: ");
                    printChar(data);
                    printf("\n");
                    free(data);
                }
                break;
            }
            case 3: {
                void *data = peek(&queue);
                if (data != NULL) {
                    printf("最前面的的元素是: ");
                    printChar(data);
                    printf("\n");
                }
                break;
            }
            case 4: {
                printf("队列中的元素如下: ");
                printQueue(&queue, &printChar);
                break;
            }
            case 5: {
                printf("队列中的节点有: %d个\n", queueSize(&queue));
                break;
            }
            case 6: {
                if (isEmpty(&queue)) {
                    printf("队列是空的呢\n");
                } else {
                    printf("队列里面有数据在的\n");
                }
                break;
            }
            case 7: {
                destroyQueue(&queue);
                printf("要销毁队列了\n");
                break;
            }
            case 8:
                exit(0);
            default:
                printf("无效选择\n");
        }
    } while (choice != 0);

    return 0;
}
