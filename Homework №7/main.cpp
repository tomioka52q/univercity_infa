//#include <iostream>
//using namespace std;
//void calculateAverage(const int* arr, int size, double& average) {
//    int sum = 0;
//    for (int i = 0; i < size; i++) {
//        sum += arr[i];
//    }
//    average = static_cast<double>(sum) / size;
//}
//
//void printArray(const int* arr, int size) {
//    for (int i = 0; i < size; i++) {
//        cout << arr[i] << " ";
//    }
//    cout << endl;
//}
//
//int main() {
//    const int N = 5;
//    int A[N], B[N];
//    double avgA = 0.0, avgB = 0.0;
//
//    cout << "5 elements A:" << endl;
//    for (int i = 0; i < N; i++) {
//        cin >> A[i];
//    }
//
//    cout << "5 elements B:" << endl;
//    for (int i = 0; i < N; i++) {
//        cin >> B[i];
//    }
//
//    calculateAverage(A, N, avgA);
//    calculateAverage(B, N, avgB);
//
//    cout << "mas A: ";
//    printArray(A, N);
//    cout << "average A: " << avgA << endl;
//
//    cout << "mas B: ";
//    printArray(B, N);
//    cout << "average B: " << avgB << endl;
//
//    return 0;
//}


#include <iostream>
#include <set>
using namespace std;
void unionSets(const set<int>& setA, const set<int>& setB, set<int>& unionSet) {
    unionSet.clear();
    for (int elem : setA) {
        unionSet.insert(elem);
    }
    for (int elem : setB) {
        unionSet.insert(elem);
    }
}

void printEven(const set<int>& set) {
    cout << "even: ";
    for (int elem : set) {
        if (elem % 2 == 0) {
            cout << elem << " ";
        }
    }
    cout << endl;
}

int main() {
    set<int> A, B, unionSet;
    int n, elem;

    cout << "count A: ";
    cin >> n;
    cout << "elem A:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> elem;
        A.insert(elem);
    }

    cout << "count B: ";
    cin >> n;
    cout << "elem B:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> elem;
        B.insert(elem);
    }

    unionSets(A, B, unionSet);
    printEven(unionSet);

    return 0;
}
