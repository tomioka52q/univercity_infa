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
