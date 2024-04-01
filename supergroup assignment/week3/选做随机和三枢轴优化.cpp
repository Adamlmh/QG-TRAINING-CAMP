#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// ��������Ԫ�ص�ֵ
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//// ��������ŷָ��
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
//// ��������ź���
//void threePivotQuickSort(int arr[], int left, int right) {
//    if (left < right) {
//        int i, j;
//        threePivotPartition(arr, left, right, &i, &j);
//        threePivotQuickSort(arr, left, i - 1);
//        threePivotQuickSort(arr, i + 1, j - 1);
//        threePivotQuickSort(arr, j + 1, right);
//    }
//}


// ���ѡ������
int randomPivot(int arr[], int left, int right) {
    srand(time(NULL)); // �����������
    int randomIndex = left + rand() % (right - left + 1);
    swap(&arr[randomIndex], &arr[right]); // �����ѡ���Ԫ�طŵ�ĩβ��Ϊ����
    return arr[right];
}

// �ָ��
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

// ����������
void quickSort(int arr[], int left, int right) {
    if (left < right) {
        int pivotIndex = partition(arr, left, right);
        quickSort(arr, left, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, right);
    }}
    
int main() {
    int n;
    printf("����������Ĵ�С��");
    scanf("%d", &n);

    int arr[n];
    printf("������ԭʼ�����ֵ��\n");
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }

    // ��ԭʼ�����������
//    threePivotQuickSort(arr, 0, n - 1);
quickSort(arr, 0, n - 1);
    // �������������
    printf("���������飺\n");
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
