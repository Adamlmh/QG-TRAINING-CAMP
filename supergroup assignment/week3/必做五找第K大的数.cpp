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

// 找到第K大的数
int findKthLargest(int arr[], int n, int k) {
    int low = 0;
    int high = n - 1;
    int targetIndex = n - k; // 第K大的数在排序后的数组中的索引位置

    while (low <= high) {
        int pivotIndex = partition(arr, low, high);
        if (pivotIndex == targetIndex) {
            return arr[pivotIndex];
        } else if (pivotIndex < targetIndex) {
            low = pivotIndex + 1;
        } else {
            high = pivotIndex - 1;
        }
    }

    // 如果找不到第K大的数，返回一个错误值
    return -1;
}

int main() {
    int N, K;
    printf("请输入数组的长度N：");
    scanf("%d", &N);
    printf("请输入数组的元素值：");
    int arr[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }
    printf("请输入要查找的第K大的数K：");
    scanf("%d", &K);

    int result = findKthLargest(arr, N, K);
    if (result != -1) {
        printf("数组中第%d大的数是：%d\n", K, result);
    } else {
        printf("找不到第%d大的数。\n", K);
    }

    return 0;
}
