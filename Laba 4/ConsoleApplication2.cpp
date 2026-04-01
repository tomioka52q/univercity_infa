#include <iostream>
#include <vector>
#include <thread>   
#include <chrono>     
#include <algorithm>  
#include <ctime>      

using namespace std;

const int N_THRESHOLD = 1000;

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quicksortSerial(vector<int>& arr, int low, int high) {
    if (low < high) {
        int p = partition(arr, low, high);
        quicksortSerial(arr, low, p - 1);
        quicksortSerial(arr, p + 1, high);
    }
}

void quicksortParallel(vector<int>& arr, int low, int high, int num_threads) {
    if (low < high) {
        if (high - low < 10) {
            sort(arr.begin() + low, arr.begin() + high + 1);
            return;
        }

        int p = partition(arr, low, high);

        if (num_threads > 1 && (high - low) > N_THRESHOLD) {

            thread leftThread(quicksortParallel, ref(arr), low, p - 1, num_threads / 2);

            quicksortParallel(arr, p + 1, high, num_threads / 2);

            leftThread.join();
        }
        else {
            quicksortSerial(arr, low, p - 1);
            quicksortSerial(arr, p + 1, high);
        }
    }
}

int main() {
    srand(time(0));

    int sizes[] = { 100, 1000, 10000, 20000, 30000, 40000, 50000 };

    cout << "Size\tQuickSort (sec)\tQuickSort_Paral 2 thread.\tQuickSort_Paral 4 thread.\tQuickSort_Paral 8 thread." << endl;

    for (int size : sizes) {
        vector<int> original;
        for (int i = 0; i < size; i++) original.push_back(rand() % 10000);

        // 1. Обычная БС
        vector<int> a1 = original;
        auto start = chrono::high_resolution_clock::now();
        quicksortSerial(a1, 0, size - 1);
        auto end = chrono::high_resolution_clock::now();
        double t_serial = chrono::duration<double>(end - start).count();

        // 2. Параллельная (2 потока)
        vector<int> a2 = original;
        start = chrono::high_resolution_clock::now();
        quicksortParallel(a2, 0, size - 1, 2);
        end = chrono::high_resolution_clock::now();
        double t_p2 = chrono::duration<double>(end - start).count();

        // 3. Параллельная (4 потока)
        vector<int> a4 = original;
        start = chrono::high_resolution_clock::now();
        quicksortParallel(a4, 0, size - 1, 4);
        end = chrono::high_resolution_clock::now();
        double t_p4 = chrono::duration<double>(end - start).count();

        // 4. Параллельная (8 потоков)
        vector<int> a8 = original;
        start = chrono::high_resolution_clock::now();
        quicksortParallel(a8, 0, size - 1, 8);
        end = chrono::high_resolution_clock::now();
        double t_p8 = chrono::duration<double>(end - start).count();

        cout << size << "\t" << t_serial << "\t" << t_p2 << "\t" << t_p4 << "\t" << t_p8 << endl;
    }

    return 0;
}