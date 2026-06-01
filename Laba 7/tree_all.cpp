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
