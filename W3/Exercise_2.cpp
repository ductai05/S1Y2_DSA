#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
using namespace std;

void printArray(int *a, int n){
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << "\n";
}

// O(nlogn)
// mergeSort chia mang thanh 2 mang con, sort mang con va gop lai
void merge(int* &a, int l, int m, int r){
    int *temp = new int[r - l + 1];
    int idl = l, idr = m + 1, idt = 0;
    while (idl <= m || idr <= r){
        if ((idl <= m && idr <= r && a[idl] <= a[idr]) || idr > r){
            temp[idt++] = a[idl++];
        } else {
            temp[idt++] = a[idr++];
        }
    }
    for (int i = 0; i < idt; i++){
        a[l + i] = temp[i];
    }
    delete []temp;
}
void mergeSortRecursion(int* &a, int l, int r){
    if (l < r){
        int m = l + (r - l) / 2;
        mergeSortRecursion(a, l, m);
        mergeSortRecursion(a, m + 1, r);
        merge(a, l, m, r);
    }
}
void mergeSort(int* &a, int n){
    mergeSortRecursion(a, 0, n - 1);
}

// O(n)
// countingSort chi sap xep cac so >= 0 (xay dung mang dem tu 0 toi max(a[i]) V- i = [0, n-1])
void countingSort(int* &a, int n){ 
    int k = 0; for (int i = 0; i < n; i++) k = max(k, a[i]);
    int *count = new int [k + 1];
    for (int i = 0; i <= k; i++) count[i] = 0;
    for (int i = 0; i < n; i++) count[a[i]] += 1;
    for (int i = 1; i <= k; i++) count[i] += count[i - 1];

    int *aNew = new int[n];
    for (int i = n - 1; i >= 0; i--){
        aNew[count[a[i]] - 1] = a[i];
        count[a[i]] -= 1; 
    }
    for (int i = 0; i < n; i++) a[i] = aNew[i];
    delete []count; delete []aNew;
}

void countingSortByDigit(int* &a, int n, int exp) {
    int *output = new int[n];
    int count[10] = {0}; 

    for (int i = 0; i < n; i++) count[(a[i] / exp) % 10]++;
    for (int i = 1; i < 10; i++) count[i] += count[i - 1];
    
    for (int i = n - 1; i >= 0; i--) {
        output[count[(a[i] / exp) % 10] - 1] = a[i];
        count[(a[i] / exp) % 10]--;
    }
    
    for (int i = 0; i < n; i++) a[i] = output[i];
    delete[] output;
}

void radixSort(int* &a, int n) {
    int max = a[0];
    for (int i = 1; i < n; i++) if (a[i] > max) max = a[i];
    for (int exp = 1; max/exp > 0; exp *= 10) {
        countingSortByDigit(a, n, exp);
    }
}

double compare(int *a, int n, int whatSort = 1){
    auto start = chrono::high_resolution_clock::now();

    if (whatSort == 1) mergeSort(a, n);
    else if (whatSort == 2) countingSort(a, n); 
    else if (whatSort == 3) radixSort(a, n);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    if (whatSort == 1) cout << "mergeSort: " << duration.count() << " giay.\n";
    else if (whatSort == 2) cout << "countingSort: " << duration.count() << " giay.\n";
    else if (whatSort == 3) cout << "radixSort: " << duration.count() << " giay.\n";
    return duration.count();
}

int main(){
    int const SIZE = 100000;
    int const NUM_ALGO = 3;
    int* randomArr = new int [SIZE];
    for (int i = 0; i < SIZE; i++) randomArr[i] = rand() % 100000 + 1;

    double* time = new double[NUM_ALGO + 1];
    for (int i = 1; i <= NUM_ALGO; i++){
        int* testArr = new int [SIZE];
        for (int i = 0; i < SIZE; i++) testArr[i] = randomArr[i];
        time[i] = compare(testArr, SIZE, i);
    }

    cout << "\n";
    if (time[1] <= time[2] && time[1] <= time[3]) cout << "The fastest algorithm: Merge Sort.\n"; 
    else if (time[2] < time[1] && time[2] < time[3]) cout << "The fastest algorithm: Counting Sort.\n";
    else cout << "The fastest algorithm: Radix Sort.\n";

    if (time[1] >= time[2] && time[1] >= time[3]) cout << "The slowest algorithm: Merge Sort.\n";
    else if (time[2] >= time[1] && time[2] >= time[3]) cout << "The slowest algorithm: Counting Sort.\n";
    else cout << "The slowest algorithm: Radix Sort.\n";
}
