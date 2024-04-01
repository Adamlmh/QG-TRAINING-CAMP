#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// 交换两个元素的值
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//// 三枢轴快排分割函数
//void threePivotPartition(int arr[], int left, int right, int* i, int* j) {
//    if (arr[right] < arr[left])
//        swap(&arr[right], &arr[left]);
//    int pivot1 = arr[left], pivot2 = arr[right];
//    int l = left + 1, g = right - 1, k = l;
//    while (k <= g) {
//        if (arr[k] < pivot1)
//            swap(&arr[k], &arr[l++]);
//        else if (arr[k] >= pivot2) {
//            while (arr[g] > pivot2 && k < g)
//                g--;
//            swap(&arr[k], &arr[g--]);
//            if (arr[k] < pivot1)
//                swap(&arr[k], &arr[l++]);
//        }
//        k++;
//    }
//    l--, g++;
//    swap(&arr[left], &arr[l]);
//    swap(&arr[right], &arr[g]);
//    *i = l, *j = g;
//}
//
//// 三枢轴快排函数
//void threePivotQuickSort(int arr[], int left, int right) {
//    if (left < right) {
//        int i, j;
//        threePivotPartition(arr, left, right, &i, &j);
//        threePivotQuickSort(arr, left, i - 1);
//        threePivotQuickSort(arr, i + 1, j - 1);
//        threePivotQuickSort(arr, j + 1, right);
//    }
//}


// 随机选择枢轴
int randomPivot(int arr[], int left, int right) {
    srand(time(NULL)); // 设置随机种子
    int randomIndex = left + rand() % (right - left + 1);
    swap(&arr[randomIndex], &arr[right]); // 将随机选择的元素放到末尾作为枢轴
    return arr[right];
}

// 分割函数
int partition(int arr[], int left, int right) {
    int pivot = randomPivot(arr, left, right);
    int i = left - 1;

    for (int j = left; j <= right - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[right]);
    return (i + 1);
}

// 快速排序函数
void quickSort(int arr[], int left, int right) {
    if (left < right) {
        int pivotIndex = partition(arr, left, right);
        quickSort(arr, left, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, right);
    }}
    
int main() {
    int n;
    printf("请输入数组的大小：");
    scanf("%d", &n);

    int arr[n];
    printf("请输入原始数组的值：\n");
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }

    // 对原始数组进行排序
//    threePivotQuickSort(arr, 0, n - 1);
quickSort(arr, 0, n - 1);
    // 输出排序后的数组
    printf("排序后的数组：\n");
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
