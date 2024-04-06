#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP_SIZE 100 // ����ѵ��������

// �ѽ�㶨��
typedef struct Heap {
    int* array; // �������ڴ洢��Ԫ��
    int size;   // �ѵĵ�ǰ��С��Ԫ�ظ�����
    int capacity; // �ѵ����������ɴ洢Ԫ�ظ�����
} Heap;

// ������
Heap* createHeap(int capacity) {
    // �����ڴ���ѽṹ
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    // �����ڴ��������
    heap->array = (int*)malloc(capacity * sizeof(int));
    // ��ʼ���ѵĴ�СΪ0
    heap->size = 0;
    // ���öѵ�����
    heap->capacity = capacity;
    return heap;
}

// ��������Ԫ��
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// ����Ԫ��
void heapifyUp(Heap* heap, int index) {
    // ��ǰ�ڵ��������Ϊ0���ҵ�ǰ�ڵ��ֵ�����丸�ڵ��ֵʱ���������Ʋ���
    while (index > 0 && heap->array[index] > heap->array[(index - 1) / 2]) {
        // ������ǰ�ڵ����丸�ڵ��ֵ
        swap(&heap->array[index], &heap->array[(index - 1) / 2]);
        // ���µ�ǰ�ڵ������Ϊ�丸�ڵ���������������ϱȽ�
        index = (index - 1) / 2;
    }
}

// ����Ԫ��
void insert(Heap* heap, int value) {
    // �ж϶��Ƿ�����
    if (heap->size == heap->capacity) {
        printf("���������޷�����Ԫ�ء�\n");
        return;
    }
    // ����Ԫ�ط����ڶѵ�ĩβ
    heap->array[heap->size] = value;
    // �ѵĴ�С����
    heap->size++;
    // ���²����Ԫ�ؽ������Ʋ�������ά�ֶѵ�����
    heapifyUp(heap, heap->size - 1);
}

// ����Ԫ��
void heapifyDown(Heap* heap, int index) {
    int largest = index;
    int left = 2 * index + 1; // ���ӽڵ�����
    int right = 2 * index + 2; // ���ӽڵ�����

    // ������ӽڵ�����Ҵ��ڵ�ǰ�ڵ㣬��������ֵ����
    if (left < heap->size && heap->array[left] > heap->array[largest]) {
        largest = left;
    }
    // ������ӽڵ�����Ҵ��ڵ�ǰ�ڵ㣬��������ֵ����
    if (right < heap->size && heap->array[right] > heap->array[largest]) {
        largest = right;
    }
    // ������ֵ���������ڵ�ǰ�ڵ���������������Ʋ���
    if (largest != index) {
        // ������ǰ�ڵ������ֵ�ڵ��ֵ
        swap(&heap->array[index], &heap->array[largest]);
        // �����Խ���������ֵ�ڵ�������Ʋ���
        heapifyDown(heap, largest);
    }
}

// ɾ���Ѷ�Ԫ��
void deleteMax(Heap* heap) {
    // �ж϶��Ƿ�Ϊ��
    if (heap->size == 0) {
        printf("��Ϊ�գ��޷�ɾ��Ԫ�ء�\n");
        return;
    }
    // ���Ѷ�Ԫ���滻Ϊ��ĩβԪ��
    heap->array[0] = heap->array[heap->size - 1];
    // �ѵĴ�С��С
    heap->size--;
    // �ԶѶ�Ԫ�ؽ������Ʋ�������ά�ֶѵ�����
    heapifyDown(heap, 0);
}

// ��ӡ��Ԫ��
void printHeap(Heap* heap) {
    printf("�ѵĵ�ǰԪ�أ�\n");
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->array[i]);
    }
    printf("\n");
}

// ���ٶ�
void destroyHeap(Heap* heap) {
    free(heap->array);
    free(heap);
}

int main() {
    // ������
    Heap* heap = createHeap(MAX_HEAP_SIZE);
    int choice, value;

    // ��ѭ�����ṩ�Ѳ����˵�
    while (1) {
        printf("\n�Ѳ���\n");
        printf("1. ����\n");
        printf("2. ɾ���Ѷ�Ԫ��\n");
        printf("3. ��ӡ��Ԫ��\n");
        printf("4. �˳�\n");
        printf("����������ѡ��: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("������Ҫ�����ֵ: ");
                scanf("%d", &value);
                insert(heap, value);
                break;
            case 2:
                deleteMax(heap);
                printf("ɾ���Ѷ�Ԫ�سɹ���\n");
                break;
            case 3:
                printHeap(heap);
                break;
            case 4:
                // �˳��������ٶ�
                destroyHeap(heap);
                printf("�˳�����\n");
                exit(0);
            default:
                printf("��Чѡ��\n");
        }
    }

    return 0;
}
