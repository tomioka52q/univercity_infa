#include <iostream>
#include <vector>

using namespace std;

int findPeakRecursive(const vector<int>& a, int left, int right) {
    if (left >= right) {
        return a[left];
    }

    int mid = left + (right - left) / 2;

    // Сравниваем средний элемент со следующим
    if (a[mid] < a[mid + 1]) {
        return findPeakRecursive(a, mid + 1, right);
    } else {
        return findPeakRecursive(a, left, mid);
    }
}

int findPeak(const vector<int>& a, int n) {
    if (n == 1) {
        return a[0];
    }
    return findPeakRecursive(a, 0, n - 1);
}

int main() {
    int n;
    if (!(cin >> n)) return 0;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    cout << findPeak(a, n) << endl;

    return 0;
}
