#include <stdio.h>
#include <stdlib.h>

// 合并两个有序子数组
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;//左半部分的长度，包括mid
    int n2 = right - mid;//右半部分的长度，不包括mid

    // 创建临时数组
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));


    // 将数据拷贝到临时数组
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];//mid+1是右半部分的起始位置

    // 合并临时数组到原数组
    int i = 0, j = 0, k = left;
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

    // 拷贝剩余元素
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

    // 释放临时数组
    free(L);
    free(R);
}

// 递归实现归并排序
void mergeSort(int arr[], int left, int right) {
    if (left < right) {    // 递归结束条件，当left>=right时，数组只有一个元素
        int mid = left + (right - left) / 2;//这里是向下取整

        // 递归排序左半部分
        mergeSort(arr, left, mid);//mid是左半部分的最后一个元素的下标
        // 递归排序右半部分
        mergeSort(arr, mid + 1, right);

        // 合并两个有序子数组
        merge(arr, left, mid, right);//第一次归的时候，这个mid是左半部分的最后一个元素的下标，right是右半部分的最后一个元素的下标
    }
}

// 打印数组
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main(void) {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    printf("Given array is \n");
    printArray(arr, arr_size);

    mergeSort(arr, 0, arr_size - 1);

    printf("\nSorted array is \n");
    printArray(arr, arr_size);
    return 0;
}