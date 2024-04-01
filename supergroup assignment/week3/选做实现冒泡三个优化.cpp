#include <stdio.h>

// ð������
void bubbleSort(int arr[], int n) {
    int i, j;
    int swapped; // ����Ƿ����˽���

    for (i = 0; i < n - 1; i++) {
        swapped = 0; // ÿ��ð�ݿ�ʼʱ��������־��Ϊ0

        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // ���� arr[j] �� arr[j + 1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1; // �����˽���
            }
        }

        // �������ð��û�з�����������˵�������Ѿ����򣬿�����ǰ��������
        if (!swapped) {
            break;
        }
    }
}

int main() {
    int n;
    printf("����������ĳ��ȣ�");
    scanf("%d", &n);

    int arr[n];
    printf("������ %d ��������Ϊ����Ԫ�أ�\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("ԭʼ���飺");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    bubbleSort(arr, n);

    printf("���������飺");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
