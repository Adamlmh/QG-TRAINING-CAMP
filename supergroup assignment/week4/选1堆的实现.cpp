#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP_SIZE 100 // 定义堆的最大容量

// 堆结点定义
typedef struct Heap {
    int* array; // 数组用于存储堆元素
    int size;   // 堆的当前大小（元素个数）
    int capacity; // 堆的容量（最大可存储元素个数）
} Heap;

// 创建堆
Heap* createHeap(int capacity) {
    // 分配内存给堆结构
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    // 分配内存给堆数组
    heap->array = (int*)malloc(capacity * sizeof(int));
    // 初始化堆的大小为0
    heap->size = 0;
    // 设置堆的容量
    heap->capacity = capacity;
    return heap;
}

// 交换两个元素
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 上移元素
void heapifyUp(Heap* heap, int index) {
    // 当前节点的索引不为0，且当前节点的值大于其父节点的值时，进行上移操作
    while (index > 0 && heap->array[index] > heap->array[(index - 1) / 2]) {
        // 交换当前节点与其父节点的值
        swap(&heap->array[index], &heap->array[(index - 1) / 2]);
        // 更新当前节点的索引为其父节点的索引，继续向上比较
        index = (index - 1) / 2;
    }
}

// 插入元素
void insert(Heap* heap, int value) {
    // 判断堆是否已满
    if (heap->size == heap->capacity) {
        printf("堆已满，无法插入元素。\n");
        return;
    }
    // 将新元素放置在堆的末尾
    heap->array[heap->size] = value;
    // 堆的大小增加
    heap->size++;
    // 对新插入的元素进行上移操作，以维持堆的性质
    heapifyUp(heap, heap->size - 1);
}

// 下移元素
void heapifyDown(Heap* heap, int index) {
    int largest = index;
    int left = 2 * index + 1; // 左子节点索引
    int right = 2 * index + 2; // 右子节点索引

    // 如果左子节点存在且大于当前节点，则更新最大值索引
    if (left < heap->size && heap->array[left] > heap->array[largest]) {
        largest = left;
    }
    // 如果右子节点存在且大于当前节点，则更新最大值索引
    if (right < heap->size && heap->array[right] > heap->array[largest]) {
        largest = right;
    }
    // 如果最大值索引不等于当前节点索引，则进行下移操作
    if (largest != index) {
        // 交换当前节点与最大值节点的值
        swap(&heap->array[index], &heap->array[largest]);
        // 继续对交换后的最大值节点进行下移操作
        heapifyDown(heap, largest);
    }
}

// 删除堆顶元素
void deleteMax(Heap* heap) {
    // 判断堆是否为空
    if (heap->size == 0) {
        printf("堆为空，无法删除元素。\n");
        return;
    }
    // 将堆顶元素替换为堆末尾元素
    heap->array[0] = heap->array[heap->size - 1];
    // 堆的大小减小
    heap->size--;
    // 对堆顶元素进行下移操作，以维持堆的性质
    heapifyDown(heap, 0);
}

// 打印堆元素
void printHeap(Heap* heap) {
    printf("堆的当前元素：\n");
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->array[i]);
    }
    printf("\n");
}

// 销毁堆
void destroyHeap(Heap* heap) {
    free(heap->array);
    free(heap);
}

int main() {
    // 创建堆
    Heap* heap = createHeap(MAX_HEAP_SIZE);
    int choice, value;

    // 主循环，提供堆操作菜单
    while (1) {
        printf("\n堆操作\n");
        printf("1. 插入\n");
        printf("2. 删除堆顶元素\n");
        printf("3. 打印堆元素\n");
        printf("4. 退出\n");
        printf("请输入您的选择: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("请输入要插入的值: ");
                scanf("%d", &value);
                insert(heap, value);
                break;
            case 2:
                deleteMax(heap);
                printf("删除堆顶元素成功。\n");
                break;
            case 3:
                printHeap(heap);
                break;
            case 4:
                // 退出程序，销毁堆
                destroyHeap(heap);
                printf("退出程序。\n");
                exit(0);
            default:
                printf("无效选择。\n");
        }
    }

    return 0;
}
