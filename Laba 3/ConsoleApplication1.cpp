#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

void combSort(int* arr, int n) {
    int gap = n;
    while (gap > 1) {
        gap = (int)(gap / 1.3);
        if (gap < 1) gap = 1;
        int i = 0;
        while (i + gap < n) {
            if (arr[i] > arr[i + gap]) {
                int temp = arr[i];
                arr[i] = arr[i + gap];
                arr[i + gap] = temp;
            }
            i = i + 1;
        }
    }
}

void quickSort(int* arr, int low, int high) {
    if (low >= high) return;
    int pivot = arr[high], i = low;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) std::swap(arr[i++], arr[j]);
    }
    std::swap(arr[i], arr[high]);
    quickSort(arr, low, i - 1);
    quickSort(arr, i + 1, high);
}

void radixSort(std::vector<int>& arr) {
    if (arr.empty()) return;
    int maxVal = *std::max_element(arr.begin(), arr.end());
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        std::vector<int> buckets[10];
        for (int x : arr) buckets[(x / exp) % 10].push_back(x);
        arr.clear();
        for (int i = 0; i < 10; i++) {
            for (int x : buckets[i]) arr.push_back(x);
        }
    }
}

void runTest(int size) {
    vector<int> base(size);
    auto seed = system_clock::now().time_since_epoch().count();
    default_random_engine dre(seed);
    uniform_int_distribution<int> di(0, 100000);

    for (int i = 0; i < size; i++) base[i] = di(dre);

    cout << "--- Test for massive size " << size << endl;

    int* combData = new int[size];
    copy(base.begin(), base.end(), combData);
    auto start = high_resolution_clock::now();
    combSort(combData, size);
    auto stop = high_resolution_clock::now();
    cout << "Comb Sort: " << duration_cast<milliseconds>(stop - start).count() << " mc" << endl;
    delete[] combData;

    int* quickData = new int[size];
    copy(base.begin(), base.end(), quickData);
    start = high_resolution_clock::now();
    quickSort(quickData, 0, size - 1);
    stop = high_resolution_clock::now();
    cout << "Quick Sort: " << duration_cast<milliseconds>(stop - start).count() << " mc" << endl;
    delete[] quickData;

    vector<int> radixData = base;
    start = high_resolution_clock::now();
    radixSort(radixData);
    stop = high_resolution_clock::now();
    cout << "Radix Sort: " << duration_cast<milliseconds>(stop - start).count() << " mc" << endl << endl;
}

int main() {
    runTest(1000);
    runTest(10000);
    runTest(50000);
    runTest(100000);
    runTest(500000);
    runTest(1000000);

    return 0;
}