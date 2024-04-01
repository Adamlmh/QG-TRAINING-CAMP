#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

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

int main() {
    int sizes[] = {100,500}; // ������Ϊ 100 ��������²���

    for (int k = 0; k < sizeof(sizes) / sizeof(sizes[0]); k++) {
        int n = sizes[k];
        int arr[n];

        // �����������
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % n;
        }

        printf("���� %d ��Ԫ��100k�Σ�\n", n);
	for(int k=1;k<=5;k++) {
	        // ��¼��ʼʱ��
        struct timeval start, end;
        gettimeofday(&start, NULL);

        // ִ�������㷨 100k ��
        for (int i = 0; i < 100000; i++) {
            // ÿ������ǰ���������������
            for (int j = 0; j < n; j++) {
                arr[j] = rand() % n;
            }

            // ����ִ�������㷨��������Ҫѡ���Ӧ��������
            if(k==1){
            	InsertSort(arr, n);
			}
            if(k==2){
             MergeSort(arr, 0, n - 1);
			}
            if(k==3){
             QuickSort(arr, 0, n - 1);
			}
            if(k==4){
             CountSort(arr, n);          
			}
            if(k==5){
            RadixCountSort(arr, n);        
			}									             
        }

        // ��¼����ʱ��
        gettimeofday(&end, NULL);

        // ����ʱ���
        long long time_taken = (end.tv_sec - start.tv_sec) * 1000000LL;
        time_taken += (end.tv_usec - start.tv_usec);
            if(k==1){
            	printf("����");
			}
            if(k==2){
            	printf("�鲢");
			}
            if(k==3){
         	printf("����");
			}
            if(k==4){
            	printf("����");             
			}
            if(k==5){
            	printf("��������");            
			}	
        // ���ƽ������ʱ��
        printf("������ʱ��%lld ΢��\n", time_taken / 100000);	
		
		
	}

    }

    return 0;
}
