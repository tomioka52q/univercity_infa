import matplotlib.pyplot as plt
sizes = [1000, 10000, 50000, 100000, 500000, 1000000]

comb_sort = [0, 1, 8, 18, 105, 265]
quick_sort = [0, 1, 7, 17, 97, 238]
radix_sort = [0, 2, 13, 31, 189, 332]

plt.figure(figsize=(10, 6))

plt.plot(sizes, comb_sort, marker='o', linestyle='-', label='Comb Sort')
plt.plot(sizes, quick_sort, marker='s', linestyle='--', label='Quick Sort')
plt.plot(sizes, radix_sort, marker='^', linestyle='-.', label='Radix Sort')

plt.title('Сравнение скорости алгоритмов сортировки', fontsize=14)
# Используем логарифмическую шкалу для X, чтобы маленькие значения не слипались
plt.xscale('log') 
plt.xlabel('Размер массива (n)', fontsize=12)
plt.ylabel('Время выполнения (мс)', fontsize=12)

# Добавление сетки и легенды
plt.grid(True, which="both", ls="-", alpha=0.5)
plt.legend()

# Отображение
plt.show()

