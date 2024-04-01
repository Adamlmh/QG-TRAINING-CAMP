#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// ��ȡ�ļ��е����ݵ�����
void readArrayFromFile(int arr[], int n, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("�޷����ļ� %s\n", filename);
        return;
    }

    for (int i = 0; i < n; i++) {
        if (fscanf(fp, "%d", &arr[i]) != 1) {
            printf("��ȡ�ļ� %s ����\n", filename);
            break;
        }
    }

    fclose(fp);
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

// ��������
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

// �鲢����
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

// ��������
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

// ��������
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

// ��������������
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

// ������������
void RadixCountSort(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max)
            max = arr[i];
    }

    for (int exp = 1; max / exp > 0; exp *= 10)
        CountSortForRadix(arr, n, exp);
}

// ��ʾ�˵�
void displayMenu() {
    printf("\n��ѡ�������㷨��\n");
    printf("1. ��������\n");
    printf("2. �鲢����\n");
    printf("3. ��������\n");
    printf("4. ��������\n");
    printf("5. ������������\n");
    printf("��ѡ��");
}

// ������
int main() {
    int dataSize, numTests;
    char filename[100];
    int arr[200000]; // �������������Ϊ 200000

    // ��ȡ�û����룺���ݴ�С�����Դ������ļ���
    printf("���������ݴ�С��");
    scanf("%d", &dataSize);
    printf("��������Դ�����");
    scanf("%d", &numTests);
    printf("�������ļ�����");
    scanf("%s", filename);

    int choice;
    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("ʹ�ò�������\n");
                break;
            case 2:
                printf("ʹ�ù鲢����\n");
                break;
            case 3:
                printf("ʹ�ÿ�������\n");
                break;
            case 4:
                printf("ʹ�ü�������\n");
                break;
            case 5:
                printf("ʹ�û�����������\n");
                break;
            default:
                printf("��Ч��ѡ����������롣\n");
                break;
        }
    } while (choice < 1 || choice > 5);
        // ��¼��ʼʱ��
        struct timeval start, end;
        gettimeofday(&start, NULL);
    for (int i = 0; i < numTests; i++) {
        char inputFilename[100];
        sprintf(inputFilename, "%s_%d.txt", filename, i + 1);

        // ���ļ��ж�ȡ����
        readArrayFromFile(arr, dataSize, inputFilename);

        // �����û�ѡ��������㷨ִ����Ӧ������
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

        // ������������д���ļ�
        char outputFilename[100];
        sprintf(outputFilename, "sorted_%s_%d.txt", filename, i + 1);
        writeArrayToFile(arr, dataSize, outputFilename);
    }
        // ��¼����ʱ��
        gettimeofday(&end, NULL);

        // ����ʱ���
        long long time_taken = (end.tv_sec - start.tv_sec) * 1000000LL;
        time_taken += (end.tv_usec - start.tv_usec);

        // ���ƽ������ʱ��
        printf("��ʱ��%lld ΢��\n", time_taken / 100000);
        printf("����ʾ΢������С˵������������������������������");
    printf("������ɣ�����������浽�ļ���\n");

    return 0;
}
