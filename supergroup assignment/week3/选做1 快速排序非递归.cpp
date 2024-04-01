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

// �ǵݹ�汾�Ŀ�������
void quickSort(int arr[], int n) {
    int stack[n * 2]; // ʹ��ջ���洢���������ʼ�ͽ���λ��
    int top = -1;
    stack[++top] = 0;
    stack[++top] = n - 1;

    while (top >= 0) {
        int end = stack[top--];
        int start = stack[top--];

        int pivotIndex = partition(arr, start, end);

        // �������������п�������
        if (pivotIndex - 1 > start) {
            stack[++top] = start;
            stack[++top] = pivotIndex - 1;
        }

        // ���Ҳ���������п�������
        if (pivotIndex + 1 < end) {
            stack[++top] = pivotIndex + 1;
            stack[++top] = end;
        }
    }
}

int main() {
    int n;
    printf("����������ĳ��ȣ�");
    scanf("%d", &n);

    int arr[n];
    printf("�����������Ԫ��ֵ��");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("ԭʼ���飺");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    quickSort(arr, n);

    printf("���������飺");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
