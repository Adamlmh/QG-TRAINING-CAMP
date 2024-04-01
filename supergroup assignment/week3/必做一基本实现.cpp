#include <stdio.h>

// ��������
void InsertSort(int arr[], int n) {
    int i, j, key;
    for (i = 1; i < n; i++) {
        key = arr[i]; // ѡȡ��ǰԪ��
        j = i - 1;
        // ���ȵ�ǰԪ�ش��Ԫ�������ƶ�
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        // ����ǰԪ�ز�����ʵ�λ��
        arr[j + 1] = key;
    }
}

// �鲢����
void Merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // ������ʱ����洢���������ֵ�Ԫ��
    int L[n1], R[n2];

    // �����ݸ��Ƶ���ʱ������
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // �ϲ�������ʱ���鵽ԭ����
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

    // ��ʣ��Ԫ�ظ��Ƶ�ԭ����
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
        // �ݹ�ض����������ֽ��й鲢����
        MergeSort(arr, l, m);
        MergeSort(arr, m + 1, r);
        // �ϲ������Ľ��
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
            // ����Ԫ��λ��
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    // ������Ԫ�طŵ���ȷ��λ��
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void QuickSort(int arr[], int low, int high) {
    if (low < high) {
        // ��ȡ����Ԫ�ص�λ��
        int pi = Partition(arr, low, high);

        // �ֱ���������������ֽ��п�������
        QuickSort(arr, low, pi - 1);
        QuickSort(arr, pi + 1, high);
    }
}

// ��������
void CountSort(int arr[], int n) {
    int output[n];
    int max = arr[0];
    // �ҵ������е����ֵ
    for (int i = 1; i < n; i++) {
        if (arr[i] > max)
            max = arr[i];
    }

    // �����������飬��ͳ��ÿ��Ԫ�س��ֵĴ���
    int count[max + 1];
    for (int i = 0; i < max + 1; i++)
        count[i] = 0;

    for (int i = 0; i < n; i++)
        count[arr[i]]++;

    // ����������ת��Ϊǰ׺������
    for (int i = 1; i <= max; i++)
        count[i] += count[i - 1];

    // ���ݼ������齫Ԫ�طŵ����������
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // �������Ľ�����ƻ�ԭ����
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

// ������������
void CountSort(int arr[], int n, int exp) {
    int output[n]; // ����һ����ʱ���� output�����ڴ洢�����Ľ��
    int count[10] = {0}; // ����һ���������� count������ͳ��ÿ�����ֳ��ֵĴ���

    // ͳ��ÿ�����ֳ��ֵĴ���
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // ����������ת��Ϊǰ׺������
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // �������ԭʼ���飬���ݵ�ǰλ����������
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i]; // ��ԭʼ�����е�Ԫ�ط�����ʱ���� output ����ȷλ��
        count[(arr[i] / exp) % 10]--; // ���¼�������
    }

    // ����ʱ�����е�Ԫ�ظ��ƻ�ԭʼ����
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}


void RadixCountSort(int arr[], int n) {
    int max = arr[0]; // �ҵ������е����ֵ
    for (int i = 1; i < n; i++) {
        if (arr[i] > max)
            max = arr[i];
    }

    for (int exp = 1; max / exp > 0; exp *= 10) // �Ӹ�λ��ʼ��ֱ�����λ
        CountSort(arr, n, exp); // ���������һ�μ������򣬸��ݵ�ǰλ��������
}


int main() {
    int n;
    printf("�����������С��");
    scanf("%d", &n);

    int arr[n];
    printf("����������Ԫ�أ�");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    // ��������
    InsertSort(arr, n);
    printf("�������������飺");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    // �鲢����
    MergeSort(arr, 0, n - 1);
    printf("�鲢���������飺");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    // ��������
    QuickSort(arr, 0, n - 1);
    printf("�������������飺");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    // ��������
    CountSort(arr, n);
    printf("�������������飺");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    // ������������
    RadixCountSort(arr, n);
    printf("�����������������飺");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
