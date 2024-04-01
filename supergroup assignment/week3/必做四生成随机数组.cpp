#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// 生成随机数组
void generateRandomArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % n;
    }
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

int main() {
    int dataSize, numTests;
    char filename[100];

    // 获取用户输入：数据大小和测试次数
    printf("请输入数据大小：");
    scanf("%d", &dataSize);
    printf("请输入测试次数：");
    scanf("%d", &numTests);
    printf("请输入要保存的文件名：");
    scanf("%s", filename);

    // 生成随机数组并保存到文件
    for (int i = 0; i < numTests; i++) {
        int arr[dataSize];
        generateRandomArray(arr, dataSize);
        char outputFilename[100];
        sprintf(outputFilename, "%s_%d.txt", filename, i + 1);
        writeArrayToFile(arr, dataSize, outputFilename);
    }

    printf("测试数据已生成并保存到文件。\n");

    return 0;
}
