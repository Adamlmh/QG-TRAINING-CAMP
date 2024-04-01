#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// 读取文件中的数据到数组
void readArrayFromFile(int arr[], int n, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("无法打开文件 %s\n", filename);
        return;
    }

    for (int i = 0; i < n; i++) {
        if (fscanf(fp, "%d", &arr[i]) != 1) {
            printf("读取文件 %s 错误\n", filename);
            break;
        }
    }

    fclose(fp);
}

// 将数组写入文件
void writeArrayToFile(int arr[], int n, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("无法打开文件 %s\n", filename);
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d\n", arr[i]);
    }

    fclose(fp);
}

// 插入排序
void InsertSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 归并排序
void Merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
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
        MergeSort(arr, l, m);
        MergeSort(arr, m + 1, r);
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
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void QuickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = Partition(arr, low, high);
        QuickSort(arr, low, pi - 1);
        QuickSort(arr, pi + 1, high);
    }
}

// 计数排序
void CountSort(int arr[], int n) {
    int output[n];
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max)
            max = arr[i];
    }

    int count[max + 1];
    for (int i = 0; i < max + 1; i++)
        count[i] = 0;

    for (int i = 0; i < n; i++)
        count[arr[i]]++;

    for (int i = 1; i <= max; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

// 计数排序辅助函数
void CountSortForRadix(int arr[], int n, int exp) {
    int output[n];
    int count[10] = {0};

    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

// 基数计数排序
void RadixCountSort(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max)
            max = arr[i];
    }

    for (int exp = 1; max / exp > 0; exp *= 10)
        CountSortForRadix(arr, n, exp);
}

// 显示菜单
void displayMenu() {
    printf("\n请选择排序算法：\n");
    printf("1. 插入排序\n");
    printf("2. 归并排序\n");
    printf("3. 快速排序\n");
    printf("4. 计数排序\n");
    printf("5. 基数计数排序\n");
    printf("请选择：");
}

// 主函数
int main() {
    int dataSize, numTests;
    char filename[100];
    int arr[200000]; // 假设最大数据量为 200000

    // 获取用户输入：数据大小、测试次数和文件名
    printf("请输入数据大小：");
    scanf("%d", &dataSize);
    printf("请输入测试次数：");
    scanf("%d", &numTests);
    printf("请输入文件名：");
    scanf("%s", filename);

    int choice;
    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("使用插入排序\n");
                break;
            case 2:
                printf("使用归并排序\n");
                break;
            case 3:
                printf("使用快速排序\n");
                break;
            case 4:
                printf("使用计数排序\n");
                break;
            case 5:
                printf("使用基数计数排序\n");
                break;
            default:
                printf("无效的选项，请重新输入。\n");
                break;
        }
    } while (choice < 1 || choice > 5);
        // 记录开始时间
        struct timeval start, end;
        gettimeofday(&start, NULL);
    for (int i = 0; i < numTests; i++) {
        char inputFilename[100];
        sprintf(inputFilename, "%s_%d.txt", filename, i + 1);

        // 从文件中读取数据
        readArrayFromFile(arr, dataSize, inputFilename);

        // 根据用户选择的排序算法执行相应的排序
        switch (choice) {
            case 1:
                InsertSort(arr, dataSize);
                break;
            case 2:
                MergeSort(arr, 0, dataSize - 1);
                break;
            case 3:
                QuickSort(arr, 0, dataSize - 1);
                break;
            case 4:
                CountSort(arr, dataSize);
                break;
            case 5:
                RadixCountSort(arr, dataSize);
                break;
        }

        // 将排序后的数组写回文件
        char outputFilename[100];
        sprintf(outputFilename, "sorted_%s_%d.txt", filename, i + 1);
        writeArrayToFile(arr, dataSize, outputFilename);
    }
        // 记录结束时间
        gettimeofday(&end, NULL);

        // 计算时间差
        long long time_taken = (end.tv_sec - start.tv_sec) * 1000000LL;
        time_taken += (end.tv_usec - start.tv_usec);

        // 输出平均排序时间
        printf("用时：%lld 微秒\n", time_taken / 100000);
        printf("若显示微妙数较小说明数据量不够大，请输入更大的数据量");
    printf("排序完成，并将结果保存到文件。\n");

    return 0;
}
