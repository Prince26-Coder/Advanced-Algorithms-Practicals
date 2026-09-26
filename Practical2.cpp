#include <bits/stdc++.h>
using namespace std;

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

int randomizedPartition(vector<int>& arr, int low, int high) {
    int randomIndex = low + rand() % (high - low + 1);
    swap(arr[randomIndex], arr[high]);
    return partition(arr, low, high);
}

int randomizedSelect(vector<int>& arr, int low, int high, int i) {
    if (low == high) return arr[low];

    int pivotIndex = randomizedPartition(arr, low, high);
    int k = pivotIndex - low + 1;

    if (i == k) {
        return arr[pivotIndex];
    } else if (i < k) {
        return randomizedSelect(arr, low, pivotIndex - 1, i);
    } else {
        return randomizedSelect(arr, pivotIndex + 1, high, i - k);
    }
}

int main() {
    srand(time(0));

    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) cin >> arr[i];

    int i;
    cout << "Enter i (find i-th smallest element, 1-indexed): ";
    cin >> i;

    if (i < 1 || i > n) {
        cout << "Invalid value of i.\n";
        return 0;
    }

    int result = randomizedSelect(arr, 0, n - 1, i);
    cout << "The " << i << "-th smallest element is: " << result << "\n";

    return 0;
}
