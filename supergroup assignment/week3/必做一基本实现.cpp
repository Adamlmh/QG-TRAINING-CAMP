#include <stdio.h>

// 插入排序
void InsertSort(int arr[], int n) {
    int i, j, key;
    for (i = 1; i < n; i++) {
        key = arr[i]; // 选取当前元素
        j = i - 1;
        // 将比当前元素大的元素向右移动
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        // 将当前元素插入合适的位置
        arr[j + 1] = key;
    }
}

// 归并排序
void Merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // 创建临时数组存储左右两部分的元素
    int L[n1], R[n2];

    // 将数据复制到临时数组中
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // 合并两个临时数组到原数组
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // 将剩余元素复制到原数组
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void MergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        // 递归地对左右两部分进行归并排序
        MergeSort(arr, l, m);
        MergeSort(arr, m + 1, r);
        // 合并排序后的结果
        Merge(arr, l, m, r);
    }
}

// 快速排序
int Partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            // 交换元素位置
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    // 将枢轴元素放到正确的位置
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void QuickSort(int arr[], int low, int high) {
    if (low < high) {
        // 获取枢轴元素的位置
        int pi = Partition(arr, low, high);

        // 分别对枢轴左右两部分进行快速排序
        QuickSort(arr, low, pi - 1);
        QuickSort(arr, pi + 1, high);
    }
}

// 计数排序
void CountSort(int arr[], int n) {
    int output[n];
    int max = arr[0];
    // 找到数组中的最大值
    for (int i = 1; i < n; i++) {
        if (arr[i] > max)
            max = arr[i];
    }

    // 创建计数数组，并统计每个元素出现的次数
    int count[max + 1];
    for (int i = 0; i < max + 1; i++)
        count[i] = 0;

    for (int i = 0; i < n; i++)
        count[arr[i]]++;

    // 将计数数组转换为前缀和数组
    for (int i = 1; i <= max; i++)
        count[i] += count[i - 1];

    // 根据计数数组将元素放到输出数组中
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // 将排序后的结果复制回原数组
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

// 基数计数排序
void CountSort(int arr[], int n, int exp) {
    int output[n]; // 创建一个临时数组 output，用于存储排序后的结果
    int count[10] = {0}; // 创建一个计数数组 count，用于统计每个数字出现的次数

    // 统计每个数字出现的次数
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // 将计数数组转换为前缀和数组
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // 倒序遍历原始数组，根据当前位数进行排序
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i]; // 将原始数组中的元素放入临时数组 output 的正确位置
        count[(arr[i] / exp) % 10]--; // 更新计数数组
    }

    // 将临时数组中的元素复制回原始数组
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}


void RadixCountSort(int arr[], int n) {
    int max = arr[0]; // 找到数组中的最大值
    for (int i = 1; i < n; i++) {
        if (arr[i] > max)
            max = arr[i];
    }

    for (int exp = 1; max / exp > 0; exp *= 10) // 从个位开始，直到最高位
        CountSort(arr, n, exp); // 对数组进行一次计数排序，根据当前位进行排序
}


int main() {
    int n;
    printf("请输入数组大小：");
    scanf("%d", &n);

    int arr[n];
    printf("请输入数组元素：");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    // 插入排序
    InsertSort(arr, n);
    printf("插入排序后的数组：");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    // 归并排序
    MergeSort(arr, 0, n - 1);
    printf("归并排序后的数组：");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    // 快速排序
    QuickSort(arr, 0, n - 1);
    printf("快速排序后的数组：");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    // 计数排序
    CountSort(arr, n);
    printf("计数排序后的数组：");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    // 基数计数排序
    RadixCountSort(arr, n);
    printf("基数计数排序后的数组：");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
