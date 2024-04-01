#include <stdio.h>

void sortArray(int arr[], int n) {
    int p0 = 0; // ָ��0Ӧ�÷��õ�λ��
    int p2 = n - 1; // ָ��2Ӧ�÷��õ�λ��

    for (int i = 0; i <= p2; i++) {
        if (arr[i] == 0) {
            // ��0������p0λ�ã�����p0����ƶ�һλ
            int temp = arr[i];
            arr[i] = arr[p0];
            arr[p0] = temp;
            p0++;
        } else if (arr[i] == 2) {
            // ��2������p2λ�ã�����p2��ǰ�ƶ�һλ
            int temp = arr[i];
            arr[i] = arr[p2];
            arr[p2] = temp;
            p2--;
            // ���ڽ�������ܵõ�����0����Ҫ���¼���λ��
            i--;
        }
    }
}

int main() {
    int N;
    printf("����������ĳ���N��");
    scanf("%d", &N);

    int arr[N];
    printf("�����������Ԫ��ֵ��ֻ��Ϊ0, 1��2����");
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
        if (arr[i] < 0 || arr[i] > 2) {
            printf("�����Ԫ��ֵ���Ϸ������������롣\n");
            return 1;
        }
    }

    sortArray(arr, N);

    printf("���������飺");
    for (int i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
