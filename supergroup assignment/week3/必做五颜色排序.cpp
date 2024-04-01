#include <stdio.h>

void sortArray(int arr[], int n) {
    int p0 = 0; // 指向0应该放置的位置
    int p2 = n - 1; // 指向2应该放置的位置

    for (int i = 0; i <= p2; i++) {
        if (arr[i] == 0) {
            // 将0交换到p0位置，并将p0向后移动一位
            int temp = arr[i];
            arr[i] = arr[p0];
            arr[p0] = temp;
            p0++;
        } else if (arr[i] == 2) {
            // 将2交换到p2位置，并将p2向前移动一位
            int temp = arr[i];
            arr[i] = arr[p2];
            arr[p2] = temp;
            p2--;
            // 由于交换后可能得到的是0，需要重新检查该位置
            i--;
        }
    }
}

int main() {
    int N;
    printf("请输入数组的长度N：");
    scanf("%d", &N);

    int arr[N];
    printf("请输入数组的元素值（只能为0, 1或2）：");
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
        if (arr[i] < 0 || arr[i] > 2) {
            printf("输入的元素值不合法，请重新输入。\n");
            return 1;
        }
    }

    sortArray(arr, N);

    printf("排序后的数组：");
    for (int i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
