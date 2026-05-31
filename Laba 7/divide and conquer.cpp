#include <iostream>
#include <vector>

using namespace std;

int findPeak(const vector<int>& a, int n) {
    int left = 0;
    int right = n - 1;

    while (left < right) {
        int mid = left + (right - left) / 2;

        // Сравниваем средний элемент со следующим
        if (a[mid] < a[mid + 1]) {
            left = mid + 1;
        }
        else {
            right = mid;
        }
    }
    return a[left];
}

int main() {
    int n;
    if (!(cin >> n)) return 0;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    if (n == 1) {
        cout << a[0] << endl;
        return 0;
    }

    cout << findPeak(a, n) << endl;

    return 0;
}
