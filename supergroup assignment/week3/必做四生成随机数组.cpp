#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// �����������
void generateRandomArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % n;
    }
}

// ������д���ļ�
void writeArrayToFile(int arr[], int n, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("�޷����ļ� %s\n", filename);
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

    // ��ȡ�û����룺���ݴ�С�Ͳ��Դ���
    printf("���������ݴ�С��");
    scanf("%d", &dataSize);
    printf("��������Դ�����");
    scanf("%d", &numTests);
    printf("������Ҫ������ļ�����");
    scanf("%s", filename);

    // ����������鲢���浽�ļ�
    for (int i = 0; i < numTests; i++) {
        int arr[dataSize];
        generateRandomArray(arr, dataSize);
        char outputFilename[100];
        sprintf(outputFilename, "%s_%d.txt", filename, i + 1);
        writeArrayToFile(arr, dataSize, outputFilename);
    }

    printf("�������������ɲ����浽�ļ���\n");

    return 0;
}
