#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    // Считываем количество дней
    if (!(cin >> n) || n <= 1) {
        cout << 0 << endl;
        return 0;
    }

    vector<int> prices(n);
    for (int i = 0; i < n; i++) {
        cin >> prices[i];
    }

    int max_profit = 0;

    // Проходим по массиву со второго дня
    for (int i = 1; i < n; i++) {
        // Если сегодня цена выше, чем вчера
        if (prices[i] > prices[i - 1]) {
            // Прибавляем разницу к прибыли
            max_profit += (prices[i] - prices[i - 1]);
        }
    }

    cout << max_profit << endl;

    return 0;
}
