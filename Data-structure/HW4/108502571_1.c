#include <stdio.h>
#include <stdlib.h>

void print(int arr[], int number);
void swap(int *first, int *second);
void quick_sort(int arr[], int number);

int main() {
    while (true) {
        int n;
        scanf("%d", &n);
        if (n == -1) return 0;

        int arr[1024];
        for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
        // printf("--- start sorting ---\n");
        quick_sort(arr, n);
        // printf("--- end sorting ---\n");

        print(arr, n);
    }
    return 0;
}

void print(int arr[], int number) {
    printf(">");
    for (int i = 0; i < number; i++) printf(" %d", arr[i]);
    printf("\n\n");
    return;
}

void swap(int *first, int *second) {
    *first = *first ^ *second;
    *second = *first ^ *second;
    *first = *first ^ *second;
    return;
}

void quick_sort(int arr[], int number) {
    if (number <= 1) return;

    // i: 比pivot小的0~i區間
    // j: 比pivot大的(i+2)~{j|number-1}區間
    int pivot = arr[number - 1];
    int i = 0, j = 0;

    // arr[j]==pivot時，arr[j]放在哪沒差，都會排序
    // 初次找arr[j]
    while (arr[j] < pivot && j + 1 < number) j++, i++;

    /* 特殊處理: 無法處理2 3 4 5 6 7 8 1 */
    // CASE: pivot為頭為尾，其餘已排序
    if (i == number - 1) {
        if (arr[0] > pivot){
            for (int k = number - 1; k > 0; k--) swap(arr + k, arr + (k - 1));
        }
        else
            return;
    }

    while (j < number) {
        if (arr[j] < pivot) {
            swap(arr + i, arr + j);
            i++;
        }
        j++;
    }
    swap(arr + (number - 1), arr + i);

    // D&C
    quick_sort(arr, i);                      // 前半number: (i+1)
    quick_sort(arr + (i + 1), j - (i + 1));  // (前半+pivot)(i)+1

    return;
}