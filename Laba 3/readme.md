import matplotlib.pyplot as plt

sizes = [1000, 10000, 50000, 100000, 500000, 1000000]
comb_sort = [0, 1, 8, 18, 105, 265]
quick_sort = [0, 1, 7, 17, 97, 238]
radix_sort = [0, 2, 13, 31, 189, 332]

plt.figure(figsize=(10, 6))

plt.plot(sizes, comb_sort, marker='o', label='Comb Sort')
plt.plot(sizes, quick_sort, marker='s', label='Quick Sort')
plt.plot(sizes, radix_sort, marker='^', label='Radix Sort')

plt.title('Сравнение алгоритмов сортировки')
plt.xlabel('Размер массива')
plt.ylabel('Время (мс)')

plt.grid(True)
plt.legend()

plt.show()
