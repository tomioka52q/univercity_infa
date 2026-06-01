// Задача 1 Лампочки

class TreeNode:
    def __init__(self, key, left=None, right=None):
        self.key = key      # яркость лампочки
        self.left = left    # левый потомок
        self.right = right  # правый потомок

def find_max_brightness(root):
    if root is None:
        return None
    current_brightness = root.key
    left_max = find_max_brightness(root.left)
    right_max = find_max_brightness(root.right)
  
    max_left = left_max if left_max is not None else float('-inf')
    max_right = right_max if right_max is not None else float('-inf')
    
    return max(current_brightness, max_left, max_right)

root = TreeNode(5,
    TreeNode(3, TreeNode(1), TreeNode(4)),
    TreeNode(8, None, TreeNode(10))
)

result = find_max_brightness(root)
print(f"Самая яркая лампочка имеет яркость: {result}")  # Вывод: 10


// Задача 2 Дерево - анаграмма
    
class Node:
     def __init__(self, value, left=None, right=None):
         self.value = value
         self.left = left
         self.right = right

def solution(root):
    if not root:
        return True

    def is_mirror(left_node, right_node):
        if not left_node and not right_node:
            return True

        if not left_node or not right_node:
            return False
        
        if left_node.value != right_node.value:
            return False

        return (is_mirror(left_node.left, right_node.right) and 
                is_mirror(left_node.right, right_node.left))

    return is_mirror(root.left, root.right)

# Пример использования (тест из задачи):
tree = Node(1, Node(2, Node(4), Node(3)), Node(2, Node(3), Node(4)))
print(solution(tree)) # Вернет True

// Задача 3 Разбиение дерева

#include <iostream>
#include <vector>
#include <utility>

struct Node {
    int key;
    int size;
    Node* left;
    Node* right;
};

std::pair<Node*, Node*> split(Node* root, int k) {
    if (root == nullptr) {
        return { nullptr, nullptr };
    }

    int left_size = 0;
    if (root->left != nullptr) {
        left_size = root->left->size;
    }

    if (left_size >= k) {
        std::pair<Node*, Node*> res = split(root->left, k);
        root->left = res.second;

        int l_sz = (root->left != nullptr) ? root->left->size : 0;
        int r_sz = (root->right != nullptr) ? root->right->size : 0;
        root->size = 1 + l_sz + r_sz;

        return { res.first, root };
    }
    else {
        std::pair<Node*, Node*> res = split(root->right, k - left_size - 1);
        root->right = res.first;

        int l_sz = (root->left != nullptr) ? root->left->size : 0;
        int r_sz = (root->right != nullptr) ? root->right->size : 0;
        root->size = 1 + l_sz + r_sz;

        return { root, res.second };
    }
}

void print_tree(Node* root) {
    if (root == nullptr) {
        return;
    }
    print_tree(root->left);
    std::cout << root->key << " ";
    print_tree(root->right);
}

// Функция для подсчета изначальных размеров поддеревьев после ввода
int calculate_sizes(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    root->size = 1 + calculate_sizes(root->left) + calculate_sizes(root->right);
    return root->size;
}

int main() {
    int n;
    if (!(std::cin >> n)) return 0;

    // массив указателей на узлы
    std::vector<Node*> nodes(n + 1);
    for (int i = 1; i <= n; ++i) {
        nodes[i] = new Node();
        nodes[i]->left = nullptr;
        nodes[i]->right = nullptr;
    }

    // Временные массивы, чтобы запомнить связи между вершинами
    std::vector<int> left_child(n + 1);
    std::vector<int> right_child(n + 1);

    // Считываем таблицу из условий задачи
    for (int i = 0; i < n; ++i) {
        int id, key, l, r;
        std::cin >> id >> key >> l >> r;
        nodes[id]->key = key;
        left_child[id] = l;
        right_child[id] = r;
    }

    // Считываем сколько элементов отрезать
    int k;
    std::cin >> k;

    // Связываем узлы указателями
    for (int i = 1; i <= n; ++i) {
        if (left_child[i] != -1) {
            nodes[i]->left = nodes[left_child[i]];
        }
        if (right_child[i] != -1) {
            nodes[i]->right = nodes[right_child[i]];
        }
    }

    Node* root = nodes[1];

    calculate_sizes(root);

    std::pair<Node*, Node*> res = split(root, k);

    std::cout << "First BST: ";
    print_tree(res.first);
    std::cout << "\n";

    std::cout << "Second BST: ";
    print_tree(res.second);
    std::cout << "\n";

    return 0;
}

// Задача 4 Разные деревья поиска

n = int(input())

# Создаем список (массив) для хранения ответов
# dp[i] — это сколько деревьев можно сделать из i узлов
dp = [0] * (n + 1)

# Базовый случай: для пустого дерева (0 узлов) есть 1 вариант
dp[0] = 1

# Идем по очереди от 1 узла до n
for nodes_count in range(1, n + 1):
    # Чтобы посчитать ответ для nodes_count узлов, 
    # мы по очереди ставим каждый узел в корень.
    # Если слева i узлов, то справа остается (nodes_count - 1 - i) узлов.
    for left_nodes in range(nodes_count):
        right_nodes = nodes_count - 1 - left_nodes
        
        # Варианты слева умножаем на варианты справа
        dp[nodes_count] += dp[left_nodes] * dp[right_nodes]

# Выводим готовый ответ для n узлов
print(dp[n])

// Задача 5 Числовые пути

class Node:
    def __init__(self, value, left=None, right=None):
        self.value = value
        self.left = left
        self.right = right
        
def solution(root):
    """
    На вход подается корень дерева (root). 
    Это объект, у которого есть свойства root.value, root.left и root.right.
    """
    
    def calculate_sum(node, current_number):
        # 1. Если пришли в пустое место (ребенка нет), возвращаем 0
        if node is None:
            return 0
        
        # 2. Формируем число пути. 
        # Умножаем накопленное число на 10 и прибавляем цифру в текущем узле.
        current_number = current_number * 10 + node.value
        
        # 3. Если это «лист» (нет ни левого, ни правого ребенка) — 
        # значит, путь закончен, возвращаем получившееся число.
        if node.left is None and node.right is None:
            return current_number
        
        # 4. Если есть дети, идем глубже в левое и правое поддеревья.
        # Результаты их сумм складываем между собой.
        return calculate_sum(node.left, current_number) + \
               calculate_sum(node.right, current_number)

    # Запускаем расчет от корня, изначально накопленное число равно 0
    return calculate_sum(root, 0)

# Создаем дерево из Примера 1: корень 1, дети 3 и 5
test_root = Node(1, Node(3), Node(5))

# Вызываем твою функцию
print(solution(test_root))  # Выведет 28

//Задача 6 Максимальный путь в дереве

class Node:
    def __init__(self, value, left=None, right=None):
        self.value = value
        self.left = left
        self.right = right
        
def solution(root):
    # Используем список из одного элемента, чтобы хранить глобальный максимум.
    # Это нужно, чтобы изменять его внутри вложенной функции.
    # Изначально ставим очень маленькое число.
    max_score = [-float('inf')]

    def get_max_gain(node):
        if node is None:
            return 0
        
        # Считаем максимальные очки слева и справа. 
        # Если там минус — берем 0 (просто не идем туда).
        left_gain = max(get_max_gain(node.left), 0)
        right_gain = max(get_max_gain(node.right), 0)
        
        # Считаем сумму пути, который "изгибается" в текущем узле
        # (левое поддерево + сам узел + правое поддерево)
        current_path_sum = node.value + left_gain + right_gain
        
        # Если этот путь лучше всех, что мы видели раньше — обновляем рекорд
        if current_path_sum > max_score[0]:
            max_score[0] = current_path_sum
            
        # Возвращаем родителю максимальный путь, который можно продолжить "вверх"
        # Это либо узел + левая ветка, либо узел + правая ветка
        return node.value + max(left_gain, right_gain)

    # Запускаем рекурсию
    get_max_gain(root)
    
    # Возвращаем накопленный глобальный максимум
    return max_score[0]

test_root = Node(1, Node(1), Node(2))

# Вызываем твою функцию
print(solution(test_root))

//Задача 7 Максимальная глубина

//Задача 8 Деревья – близнецы

class Node:
    def __init__(self, value, left=None, right=None):
        self.value = value
        self.left = left
        self.right = right

def solution(root1, root2):
    # Если оба пустые - они одинаковые
    if root1 is None and root2 is None:
        return True
    # Если один пустой, а другой нет - разные
    if root1 is None or root2 is None:
        return False
    # Если значения разные - разные
    if root1.value != root2.value:
        return False
    
    # Проверяем левые части и правые части
    return solution(root1.left, root2.left) and solution(root1.right, root2.right)
