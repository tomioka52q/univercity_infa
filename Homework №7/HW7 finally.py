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



def combine_even(set_a, set_b):
    union = set_a | set_b
    even_numbers = []
    for i in union:
        if i % 2 == 0:
            even_numbers.append(i)
    return sorted(even_numbers)

def main():
    print("Элементы множества A")
    A = set(map(int, input().split()))

    print("Элементы множества B")
    B = set(map(int, input().split()))

    even_elements = combine_even(A, B)

    print("Четные элементы:", even_elements)
if __name__ == "__main__":
    main()
