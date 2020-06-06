#include <iostream>
#include "SortTestHelper.h"
#include "Student.h"

using namespace std;

template<typename T>
void selectionSort(T arr[], int n) {
    for (int i = 0; i < n; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

template<typename T>
void insertionSort(T arr[], int n) {

    for (int i = 1; i < n; ++i) {

//        for (int j = i; j > 0 && arr[j] < arr[j - 1]; --j) {
//            swap(arr[j], arr[j - 1]);
//        }
        T e = arr[i];
        int j;
        for (j = i; j > 0 && arr[j - 1] > e; --j) {
            arr[j] = arr[j - 1];
        }
        arr[j] = e;
    }
}

template<typename T>
void insertionSort(T arr[], int l, int r) {
    for (int i = l + 1; i <= r; ++i) {
        T e = arr[i];
        int j;
        for (j = i; j > l && arr[j - 1] > e; --j) {
            arr[j] = arr[j - 1];
        }
        arr[j] = e;
    }
}

template<typename T>
void __merge(T arr[], int l, int mid, int r) {
    // 大数组用 new 生成，delete[] 删除
//    T aux[r - l + 1];
    T *aux = new T[r - l + 1];
    for (int i = l; i <= r; ++i) {
        aux[i - l] = arr[i];
    }
    int i = l, j = mid + 1;
    for (int k = l; k <= r; ++k) {
        if (i > mid) {
            arr[k] = aux[j - l];
            j++;
        } else if (j > r) {
            arr[k] = aux[i - l];
            i++;
        } else {
            if (aux[i - l] < aux[j - l]) {
                arr[k] = aux[i - l];
                i++;
            } else {
                arr[k] = aux[j - l];
                j++;
            }
        }
    }
    delete[] aux;
}

template<typename T>
void __mergeSort(T arr[], int l, int r) {

//    if (l >= r) {
//        return;
//    }

    // 优化1：小数据用插入排序，不再递归
    if (r - l <= 15) {
        insertionSort(arr, l, r);
        return;
    }

    int mid = (l + r) / 2;
    __mergeSort(arr, l, mid);
    __mergeSort(arr, mid + 1, r);

    // 优化2：如果 mid 比 mid + 1 还小，说明该子序列已经有序，不再需要 merge 操作
    if (arr[mid] > arr[mid + 1]) {
        __merge(arr, l, mid, r);
    }
}

// 归并排序
template<typename T>
void mergeSort(T arr[], int n) {
    __mergeSort(arr, 0, n - 1);
}

// 自底向上的归并排序
template<typename T>
void mergeSortBU(T arr[], int n) {
    for (int size = 1; size < n; size += size) {
        for (int i = 0; i + size < n; i += size + size) {
            __merge(arr, i, i + size - 1, min(i + size + size - 1, n - 1));
        }
    }
}

template<typename T>
int __partition(T arr[], int l, int r) {
    T v = arr[l];

    int j = l;
    for (int i = l + 1; i <= r; ++i) {
        if (arr[i] < v) {
            swap(arr[j + 1], arr[i]);
            j++;
        }
    }
    swap(arr[l], arr[j]);
    return j;
}

template<typename T>
void __quickSort(T arr[], int l, int r) {
    if (l >= r) {
        return;
    }
    int p = __partition(arr, l, r);
    __quickSort(arr, l, p - 1);
    __quickSort(arr, p + 1, r);
}

// 快速排序
// !!!对近乎有序的数组，快排退化成了 O(n^2) 的算法
template<typename T>
void quickSort(T arr[], int n) {
    __quickSort(arr, 0, n - 1);
}

int main() {
    int n = 1000000;
    int *arr = SortTestHelper::generateRandomArray(n, 0, n);
    int *arr2 = SortTestHelper::copyIntArray(arr, n);
    SortTestHelper::testSort("Merge Sort", mergeSort, arr, n);
    SortTestHelper::testSort("Quick Sort", quickSort, arr2, n);

    int *arr3 = SortTestHelper::generateNearlyOrderedArray(n, 10);
    int *arr4 = SortTestHelper::copyIntArray(arr3, n);
    SortTestHelper::testSort("Merge Sort", mergeSort, arr3, n);
    SortTestHelper::testSort("Quick Sort", quickSort, arr4, n);
    delete[] arr;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;


    return 0;
}
