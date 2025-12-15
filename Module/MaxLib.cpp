#include "pch.h"
#include "MaxLib.h"
#include <ctime>

extern "C" __declspec(dllexport)
double max_benchmark(const int* arr, int size, int iterations) {
    if (arr == nullptr || size <= 0 || iterations <= 0) {
        return 0.0;
    }

    clock_t start = clock();

    for (int it = 0; it < iterations; ++it) {
        int max_val = arr[0];
        for (int i = 1; i < size; ++i) {
            if (arr[i] > max_val) {
                max_val = arr[i];
            }
        }
    }

    clock_t end = clock();
    double elapsed = double(end - start) / CLOCKS_PER_SEC;
    return elapsed;
}
