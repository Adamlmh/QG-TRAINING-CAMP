#include <stdio.h>
#include <stdlib.h>

// ������нڵ�ṹ
typedef struct Node {
    void *data;
    struct Node *next;
} Node;

// ������нṹ
typedef struct {
    Node *front; // ��ͷָ��
    Node *rear;  // ��βָ��
    int size;    // ���г���
} Queue;

// ��ʼ������
void initQueue(Queue *queue) {
    queue->front = queue->rear = NULL;
    queue->size = 0;
}

// ���
void enqueue(Queue *queue, void *data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("�ڴ����ʧ������\n");
        exit(0);
    }
    newNode->data = data;
    newNode->next = NULL;

    if (queue->rear == NULL) { // ����Ϊ��
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    queue->size++;
}

// ���Ӳ����ض�ͷԪ��
void *dequeue(Queue *queue) {
    if (queue->front == NULL) {
        printf("�����ǿյ�Ӵ\n");
        return NULL;
    }

    Node *temp = queue->front;
    void *data = temp->data;
    queue->front = temp->next;
    free(temp);

    if (queue->front == NULL) { // ����Ϊ��
        queue->rear = NULL;
    }
    queue->size--;

    return data;
}

// ��ѯ���г���
int queueSize(Queue *queue) {
    return queue->size;
}

// �鿴��ͷԪ��
void *peek(Queue *queue) {
    if (queue->front == NULL) {
        printf("�����ǿյ�Ӵ\n");
        return NULL;
    }
    return queue->front->data;
}

// ��ӡ����������Ԫ��
void printQueue(Queue *queue, void (*printData)(void *)) {
    Node *current = queue->front;
    while (current != NULL) {
        printData(current->data);
        printf(" ");
        current = current->next;
    }
    printf("\n");
}

// �ж϶����Ƿ�Ϊ��
int isEmpty(Queue *queue) {
    return queue->front == NULL;
}

// ���ٶ���
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

// ��ӡ�ַ�Ԫ��
void printChar(void *data) {
    printf("%c", *((char *)data));
}

int main() {
    Queue queue;
    initQueue(&queue);
    int choice;
    do {
    printf("====================\n");
    printf("[1]\t���\n");
    printf("[2]\t����\n");
    printf("[3]\t�鿴��ͷ\n");
    printf("[4]\t��ӡ����\n");
    printf("[5]\t�жӳ���\n");
    printf("[6]\t�п�\n");
    printf("[7]\t��������\n");
    printf("[8]\t�˳�����\n");
    printf("====================\n");
        printf("���������ѡ��: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                    char *data = (char *)malloc(sizeof(char));
                    printf("��ѧ������һ���ַ�: ");
                    scanf(" %c", data);
                    enqueue(&queue, data);
                break;
            }
            case 2: {
                void *data = dequeue(&queue);
                if (data != NULL) {
                    printf("�������������Ԫ�ش������Ƴ�����: ");
                    printChar(data);
                    printf("\n");
                    free(data);
                }
                break;
            }
            case 3: {
                void *data = peek(&queue);
                if (data != NULL) {
                    printf("��ǰ��ĵ�Ԫ����: ");
                    printChar(data);
                    printf("\n");
                }
                break;
            }
            case 4: {
                printf("�����е�Ԫ������: ");
                printQueue(&queue, &printChar);
                break;
            }
            case 5: {
                printf("�����еĽڵ���: %d��\n", queueSize(&queue));
                break;
            }
            case 6: {
                if (isEmpty(&queue)) {
                    printf("�����ǿյ���\n");
                } else {
                    printf("���������������ڵ�\n");
                }
                break;
            }
            case 7: {
                destroyQueue(&queue);
                printf("Ҫ���ٶ�����\n");
                break;
            }
            case 8:
                exit(0);
            default:
                printf("��Чѡ��\n");
        }
    } while (choice != 0);

    return 0;
}
