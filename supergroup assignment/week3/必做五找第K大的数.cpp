#include <stdio.h>

// ���������еĻ��ֺ���
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            // ����arr[i]��arr[j]
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    // ������Ԫ�طŵ���ȷ��λ��
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

// �ҵ���K�����
int findKthLargest(int arr[], int n, int k) {
    int low = 0;
    int high = n - 1;
    int targetIndex = n - k; // ��K������������������е�����λ��

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

    // ����Ҳ�����K�����������һ������ֵ
    return -1;
}

int main() {
    int N, K;
    printf("����������ĳ���N��");
    scanf("%d", &N);
    printf("�����������Ԫ��ֵ��");
    int arr[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }
    printf("������Ҫ���ҵĵ�K�����K��");
    scanf("%d", &K);

    int result = findKthLargest(arr, N, K);
    if (result != -1) {
        printf("�����е�%d������ǣ�%d\n", K, result);
    } else {
        printf("�Ҳ�����%d�������\n", K);
    }

    return 0;
}
