#include <iostream>
#include <vector>
#include <string>

using namespace std;

int n, k;
int adj[20][20];
int colors[20];

// Функция проверки можно ли покрасить вершину v в цвет c
bool isSafe(int v, int c) {
    for (int i = 0; i < n; i++) {
        if (adj[v][i] && colors[i] == c) {
            return false;
        }
    }
    return true;
}

// Рекурсивная функция поиска с возвратом
bool solve(int v) {
    if (v == n) {
        return true;
    }

    // Пробуем каждый цвет от 1 до k
    for (int c = 1; c <= k; c++) {
        if (isSafe(v, c)) {
            colors[v] = c;

            if (solve(v + 1)) return true;

            colors[v] = 0;
        }
    }
    return false;
}

int main() {
    if (!(cin >> n >> k)) return 0;

    for (int i = 0; i < n; i++) {
        string row;
        cin >> row;
        for (int j = 0; j < n; j++) {
            adj[i][j] = row[j] - '0';
        }
    }

    if (solve(0)) {
        cout << "YES" << endl;
        for (int i = 0; i < n; i++) {
            cout << colors[i] << (i == n - 1 ? "" : " ");
        }
        cout << endl;
    }
    else {
        cout << "NO" << endl;
    }

    return 0;
}
