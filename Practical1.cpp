#include <bits/stdc++.h>
using namespace std;

long long comparisonCount = 0; 

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1; 
    for (int j = low; j < high; j++) {
        comparisonCount++;    
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

void randomizedQuickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = randomizedPartition(arr, low, high);
        randomizedQuickSort(arr, low, pivotIndex - 1);
        randomizedQuickSort(arr, pivotIndex + 1, high);
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

    randomizedQuickSort(arr, 0, n - 1);

    cout << "\nSorted array: ";
    for (int x : arr) cout << x << " ";
    cout << "\n";

    cout << "Number of comparisons: " << comparisonCount << "\n";

    return 0;
}
