//
// Created by bohua on 2020/6/8.
//

#ifndef ALGORITHM_BINARYSEARCH_H
#define ALGORITHM_BINARYSEARCH_H

template<typename T>
int binarySearch(T arr[], int n, T target) {

    int l = 0, r = n - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == target) {
            return mid;
        }
        if (target < arr[mid]) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return -1;
}

template<typename T>
int __binarySearch2(T arr[], int l, int r, T target) {

    if (l > r) {
        return -1;
    }

    int mid = l + (r - l) / 2;
    if (arr[mid] == target) {
        return mid;
    }
    if (target < arr[mid]) {
        __binarySearch2(arr, l, mid - 1, target);
    } else {
        __binarySearch2(arr, mid + 1, r, target);
    }

}

template<typename T>
int binarySearch2(T arr[], int n, T target) {

    return __binarySearch2(arr, 0, n - 1, target);
}

#endif //ALGORITHM_BINARYSEARCH_H
