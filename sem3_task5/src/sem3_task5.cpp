#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>
#include <string>
#include <utility>

using namespace std;
using namespace std::chrono;


void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}




void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}




void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) temp[k++] = arr[i++];
        else                  temp[k++] = arr[j++];
    }
    while (i <= mid)  temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    for (int p = 0; p < k; ++p) {
        arr[left + p] = temp[p];
    }
}

void mergeSortHelper(vector<int>& arr, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSortHelper(arr, left, mid);
    mergeSortHelper(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void mergeSort(vector<int>& arr) {
    mergeSortHelper(arr, 0, arr.size() - 1);
}




int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSortHelper(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSortHelper(arr, low, pi - 1);
        quickSortHelper(arr, pi + 1, high);
    }
}

void quickSort(vector<int>& arr) {
    quickSortHelper(arr, 0, arr.size() - 1);
}




int main() {
    const int size = 100000;

    vector<int> original(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(-1'000'000, 1'000'000);

    for (auto& x : original) {
        x = dist(gen);
    }

    cout << "Сравнение алгоритмов сортировки на " << size << " элементах\n";
    cout << "\n";

    auto measure = [&](const string& name, auto sortFunc) {
        vector<int> arr = original;

        auto start = high_resolution_clock::now();
        sortFunc(arr);
        auto end = high_resolution_clock::now();

        double ms = duration<double, milli>(end - start).count();

        cout << name << ": " << fixed << setprecision(2) << ms << " мс\n";
    };

    measure("Пузырьковая", bubbleSort);
    measure("Вставками", insertionSort);
    measure("Слиянием", mergeSort);
    measure("Быстрая", quickSort);
    measure("std::sort (быстрая)", [](vector<int>& v) { sort(v.begin(), v.end()); });

    return 0;
}
