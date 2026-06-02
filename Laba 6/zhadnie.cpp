// Задача №1 Биржа

# 1. Считываем количество дней
n = int(input().strip())

# Если дней 0 или 1, то торговать вообще не получится, прибыль всегда 0
if n <= 1:
    print(0)
else:
    # 2. Считываем все цены из второй строки в один список чисел
    # Метод split() делит строку по пробелам, а мы превращаем каждый кусочек в int
    prices = [int(x) for x in input().strip().split()]
    
    total_profit = 0
    
    # 3. Проходим циклом со второго дня (индекс 1) до самого конца
    for i in range(1, n):
        # Если сегодня (prices[i]) цена выше, чем была вчера (prices[i-1])
        if prices[i] > prices[i-1]:
            # То мы мысленно забираем эту разницу себе в прибыль
            diff = prices[i] - prices[i-1]
            total_profit += diff
            
    # 4. Выводим итоговую максимальную прибыль
    print(total_profit)

// Задача №2 Расписание

n = int(input())

lessons = []

for i in range(n):
    line = input().split()
    start_str = line[0]
    end_str = line[1]

    start_float = float(start_str)
    end_float = float(end_str)

    lessons.append([end_float, start_float, start_str, end_str])

lessons.sort()

ans = []
last_end_time = -1.0

for lesson in lessons:
    end_float = lesson[0]
    start_float = lesson[1]
    start_str = lesson[2]
    end_str = lesson[3]

    if start_float >= last_end_time:
        ans.append(start_str + " " + end_str)
        last_end_time = end_float
print(len(ans))

for lesson_str in ans:
    print(lesson_str)

// Задача №3 Золотая лихорадка

# 1. Считываем общую вместимость рюкзака M
m_capacity = int(input().strip())

# 2. Считываем количество куч золота n
n = int(input().strip())

piles = []

# 3. В цикле собираем все кучи в один список
for _ in range(n):
    parts = input().strip().split()
    if len(parts) == 2:
        c = int(parts[0])  # стоимость за 1 кг
        m = int(parts[1])  # сколько всего килограмм в куче
        piles.append([c, m])

# 4. Сортируем кучи по цене за килограмм в убывающем порядке (от самых дорогих к дешевым).
# Флаг reverse=True как раз разворачивает список наоборот.
piles.sort(reverse=True)

total_cost = 0
remaining_capacity = m_capacity

# 5. Идем по отсортированным кучам и гребем золото
for pile in piles:
    c = pile[0]
    m = pile[1]
    
    # Если место в рюкзаке закончилось — выходим из цикла
    if remaining_capacity == 0:
        break
        
    # Если куча целиком влезает в рюкзак
    if m <= remaining_capacity:
        take = m
    else:
        # Если куча целиком не влезает, берем только остаток места
        take = remaining_capacity
        
    # Считаем стоимость того, что взяли, и уменьшаем свободное место
    total_cost += take * c
    remaining_capacity -= take

# 6. Выводим итоговую максимальную стоимость
print(total_cost)


//Задача №4 Алла на Алгосах

x = int(input())  # Нужная сумма франков
k = int(input())  # Сколько видов купюр у нас есть

nominal_strings = input().split()

coins = []
for s in nominal_strings:
    coins.append(int(s))
    
dp = [999999] * (x + 1)

dp[0] = 0

for i in range(1, x + 1):

    for coin in coins:

        if coin <= i:

            variant = dp[i - coin] + 1

            if variant < dp[i]:
                dp[i] = variant

if dp[x] == 999999:
    print(-1)
else:
    print(dp[x])

//Задача №5 Прыжки по лестнице

n, k = map(int, input().split())

MOD = 10**9 + 7

dp = [0] * (n + 1)

dp[1] = 1

for i in range(2, n + 1):
    start = max(1, i - k)

    for j in range(start, i):
        dp[i] = (dp[i] + dp[j]) % MOD
        
print(dp[n])

//Задача №6 Банкомат

m = int(input().strip())  # Целевая сумма
n = int(input().strip())  # Количество номиналов купюр

coins = [int(x) for x in input().strip().split()]

dp = [0] * (m + 1)

dp[0] = 1

for coin in coins:

    for i in range(coin, m + 1):

        dp[i] += dp[i - coin]

print(dp[m])


//Задача №7 Поле с цветочками

n, m = map(int, input().split())

grid = []
for _ in range(n):
    grid.append([int(x) for x in input().strip()])

grid.reverse()

dp = [[0] * (m + 1) for _ in range(n + 1)]

for i in range(1, n + 1):
    for j in range(1, m + 1):

        from_top = dp[i - 1][j]
        from_left = dp[i][j - 1]

        dp[i][j] = max(from_top, from_left) + grid[i - 1][j - 1]
print(dp[n][m])


// Задача №8 Гороскопы

# 1. Считываем данные
n = int(input())
a = [int(x) for x in input().split()]
m = int(input())
b = [int(x) for x in input().split()]

# 2. Создаем пустую таблицу, заполненную нулями.
# Строк у нас n+1, столбцов m+1 (лишний нулевой ряд нужен для удобства)
dp = [[0] * (m + 1) for _ in range(n + 1)]

# Заполняем таблицу
for i in range(1, n + 1):
    for j in range(1, m + 1):
        # Если элементы совпали (помним, что в списках 'a' и 'b' 
        # индексы начинаются с 0, поэтому пишем i-1 и j-1)
        if a[i - 1] == b[j - 1]:
            # Берем значение по диагонали (до этого совпадения) и добавляем 1
            dp[i][j] = dp[i - 1][j - 1] + 1
        else:
            # Если не совпали, берем максимум из соседа сверху и соседа слева
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])

# В самой последней ячейке таблицы теперь лежит правильный ответ — длина НОП
print(dp[n][m])


# 3. Восстанавливаем индексы. Начинаем с правого нижнего угла (n, m)
ind_a, ind_b = [], []
i, j = n, m

# Пока не уперлись в левую или верхнюю стенку (в нулевые ряды)
while i > 0 and j > 0:
    # Если элементы в текущей строке и столбце одинаковые — мы нашли участника НОП!
    if a[i - 1] == b[j - 1]:
        ind_a.append(i)  # Сохраняем индекс для первой последовательности
        ind_b.append(j)  # Сохраняем индекс для второй последовательности
        i -= 1           # Шагаем по диагонали вверх...
        j -= 1           # ...и влево
    
    # Если элементы не совпали, смотрим, откуда пришло это число в таблицу.
    # Если сверху значение больше или такое же, значит, идем вверх
    elif dp[i - 1][j] >= dp[i][j - 1]:
        i -= 1
    # Иначе — идем влево
    else:
        j -= 1

# 4. Так как мы шли с конца к началу, списки индексов получились перевернутыми.
# Разворачиваем их с помощью [::-1] и выводим на экран через пробел (*)
print(*ind_a[::-1])
print(*ind_b[::-1])


// Задача №9 Золото лепреконов

# 1. Считываем количество слитков и вместимость рюкзака
n, M = map(int, input().split())

# Считываем веса всех слитков
weights = [int(x) for x in input().split()]

# 2. Создаем массив состояний. dp[i] показывает, можно ли набрать вес i
dp = [False] * (M + 1)
dp[0] = True  # Вес 0 можно собрать всегда

# 3. Перебираем каждый слиток
for w in weights:
    # Идем от максимальной вместимости M вниз до веса слитка w
    for i in range(M, w - 1, -1):
        if dp[i - w]:
            dp[i] = True

# 4. Ищем самый большой вес, который удалось собрать (идем с конца массива)
for i in range(M, -1, -1):
    if dp[i]:
        print(i)
        break

// Задача №10 Гоша в ресторане

n = int(input())
costs = [int(input()) for _ in range(n)]

INF = float('inf')
# Создаем таблицу: строк n+1, столбцов n+2 (с запасом для j+1)
dp = [[INF] * (n + 2) for _ in range(n + 1)]
dp[0][0] = 0

# 1. Заполняем DP-таблицу
for i in range(1, n + 1):
    p = costs[i - 1]
    for j in range(n + 1):
        # Если платим деньгами, смотрим, прибавился ли купон (если p > 500)
        prev_j = j - 1 if p > 500 else j
        pay = dp[i - 1][prev_j] + p if prev_j >= 0 else INF
        
        # Если используем купон, то вчера их было на один больше (j + 1)
        free = dp[i - 1][j + 1]
        
        dp[i][j] = min(pay, free)

# 2. Находим минимальную стоимость и индекс оставшихся купонов
min_cost = min(dp[n])
best_j = dp[n].index(min_cost)

# 3. Восстанавливаем дни, когда тратили купоны
coupon_days = []
curr_j = best_j
for i in range(n, 0, -1):
    # Если значение пришло из j + 1, значит, в этот день был использован купон
    if dp[i - 1][curr_j + 1] == dp[i][curr_j]:
        coupon_days.append(i)
        curr_j += 1
    elif costs[i - 1] > 500:
        curr_j -= 1

# 4. Выводим результат
print(min_cost, len(coupon_days))
print(*coupon_days[::-1])
