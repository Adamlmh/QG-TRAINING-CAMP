#include <stdio.h>

// 冒泡排序
void bubbleSort(int arr[], int n) {
    int i, j;
    int swapped; // 标记是否发生了交换

    for (i = 0; i < n - 1; i++) {
        swapped = 0; // 每轮冒泡开始时将交换标志置为0

        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // 交换 arr[j] 和 arr[j + 1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1; // 发生了交换
            }
        }

        // 如果本轮冒泡没有发生交换，则说明数组已经有序，可以提前结束排序
        if (!swapped) {
            break;
        }
    }
}

int main() {
    int n;
    printf("请输入数组的长度：");
    scanf("%d", &n);

    int arr[n];
    printf("请输入 %d 个整数作为数组元素：\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("原始数组：");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    bubbleSort(arr, n);

    printf("排序后的数组：");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
