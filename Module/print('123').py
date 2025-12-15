import random
import time
from ctypes import CDLL, POINTER, c_int, c_double

lib = CDLL("./Dll1.dll")

lib.max_benchmark.argtypes = [POINTER(c_int), c_int, c_int]
lib.max_benchmark.restype = c_double


def cpp_max_time(array_size, iterations):
    data = [random.randint(-1_000_000, 1_000_000) for _ in range(array_size)]
    c_array = (c_int * array_size)(*data)
    t = lib.max_benchmark(c_array, array_size, iterations)
    return round(t, 2)


def python_max_time(array_size, iterations):
    data = [random.randint(-1_000_000, 1_000_000) for _ in range(array_size)]
    start = time.time()
    for _ in range(iterations):
        max_val = data[0]
        for x in data[1:]:
            if x > max_val:
                max_val = x
    end = time.time()
    return round(end - start, 2)


if __name__ == "__main__":
    array_size = 1000
    tests = [
        (1, 10_000),
        (2, 50_000),
        (3, 100_000),
    ]

    results = []
    for test_id, iters in tests:
        t_cpp = cpp_max_time(array_size, iters)
        t_py = python_max_time(array_size, iters)
        results.append((test_id, iters, t_cpp, t_py))
        print(f"{test_id:6} | {iters:8} | {t_cpp:6.2f} | {t_py:8.2f}")
    for test_id, iters, t_cpp, t_py in results:
        print(f"| {test_id} | {iters} | {t_cpp:.2f} | {t_py:.2f} |")
