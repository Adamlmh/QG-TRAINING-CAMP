#include <stdio.h>

// 快速排序中的划分函数
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            // 交换arr[i]和arr[j]
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    // 将枢轴元素放到正确的位置
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

// 非递归版本的快速排序
void quickSort(int arr[], int n) {
    int stack[n * 2]; // 使用栈来存储子数组的起始和结束位置
    int top = -1;
    stack[++top] = 0;
    stack[++top] = n - 1;

    while (top >= 0) {
        int end = stack[top--];
        int start = stack[top--];

        int pivotIndex = partition(arr, start, end);

        // 对左侧子数组进行快速排序
        if (pivotIndex - 1 > start) {
            stack[++top] = start;
            stack[++top] = pivotIndex - 1;
        }

        // 对右侧子数组进行快速排序
        if (pivotIndex + 1 < end) {
            stack[++top] = pivotIndex + 1;
            stack[++top] = end;
        }
    }
}

int main() {
    int n;
    printf("请输入数组的长度：");
    scanf("%d", &n);

    int arr[n];
    printf("请输入数组的元素值：");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("原始数组：");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    quickSort(arr, n);

    printf("排序后的数组：");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
