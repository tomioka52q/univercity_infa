#1
"""def average(arr):
    count = 0
    for i in range(len(arr)):
        count += arr[i]
    return count / len(arr)

A = []
B = []
size = 5
print(f"{size} элементов для A:")
for i in range(size):
    A.append(int(input()))

print(f"{size} элементов для B:")
for i in range(size):
    B.append(int(input()))

avgA = average(A)
avgB = average(B)

print(A)
print(B)
print(f"Среднее арифметическое A: {avgA}")
print(f"Среднее арифметическое B: {avgB}")"""


def even(number):
    return number % 2 == 0

def combine(set_a, set_b):
    combined = []

    for item in set_a:
        if item not in combined:
            combined.append(item)

    for item in set_b:
        if item not in combined:
            combined.append(item)
    
    return combined

def evens(combined_set):
    even_numbers = []
    for number in combined_set:
        if even(number):
            even_numbers.append(number)
    return sorted(even_numbers)

def main():
    print("Элементы множества A")
    A = set(map(int, input().split()))

    print("Элементы множества B")
    B = set(map(int, input().split()))
    
    # Обработка данных через функции
    combined = combine(A, B)
    even_elements = evens(combined)
    
    if even_elements:
        print("Четные элементы:", even_elements)
if __name__ == "__main__":
    main()
