//
// Created by bohua on 2020/6/6.
//

#include <iostream>
#include <algorithm>
#include <ctime>
#include <cassert>
#include "SortTestHelper.h"

#include "Heap.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "QuickSort3Ways.h"

template<typename T>
void heapSort1(T arr[], int n) {
    MaxHeap<T> maxHeap = MaxHeap<T>(n);
    for (int i = 0; i < n; i++) {
        maxHeap.insert(arr[i]);
    }
    for (int i = n - 1; i >= 0; --i) {
        arr[i] = maxHeap.extractMax();
    }
}

int main() {
    int n = 1000000;

    cout << "Test for Random Array, size = " << n << ", random range [0," << n << "]" << endl;
    int *arr1 = SortTestHelper::generateRandomArray(n, 0, n);
    int *arr2 = SortTestHelper::copyIntArray(arr1, n);
    int *arr3 = SortTestHelper::copyIntArray(arr1, n);
    int *arr4 = SortTestHelper::copyIntArray(arr1, n);

    SortTestHelper::testSort("Merge Sort", mergeSort, arr1, n);
    SortTestHelper::testSort("Quick Sort", quickSort, arr2, n);
    SortTestHelper::testSort("Quick Sort 3 Ways", quickSort3Ways, arr3, n);
    SortTestHelper::testSort("Heap Sort 1", heapSort1, arr4, n);

    delete [] arr1;
    delete [] arr2;
    delete [] arr3;
    delete [] arr4;

    return 0;
}