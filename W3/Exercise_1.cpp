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

// quickSort chon pivot (diem chot), cac phan tu < pivot nam ben trai, > pivot nam ben phai
void partition(int* &a, int l, int r, int &p){
    int mid = l + (r - l) / 2;
    if (a[mid] < a[l]) swap(a[mid], a[l]);
    if (a[r] < a[l]) swap(a[r], a[l]);
    if (a[mid] < a[r]) swap(a[mid], a[r]);

    int pivot = a[r];
    int i = l - 1;
    for (int j = l; j < r; j++){
        if (a[j] < pivot){
            i++;
            swap(a[i], a[j]); // a[j] di truoc a[i], vi a[j] < pivot nen doi cho a[i] va a[j]
        }
    }
    swap(a[i + 1], a[r]); // pivot di sau a[i], vi pivot > a[i]
    p = i + 1;
}
void quickSortRecursion(int* &a, int l, int r){
    if (l < r){
        int p;
        partition(a, l, r, p);
        quickSortRecursion(a, l, p - 1);
        quickSortRecursion(a, p + 1, r);
    }
}
void quickSort(int* &a, int n){
    quickSortRecursion(a, 0, n - 1);
}

// heapSort chuyen mang thanh heap (nut i > nut 2*i + 1 va 2*i + 2)
// build heap tu phan tu n/2-1 -> 0
// swap a[0] (dau heap) <-> cuoi mang; maxHeapify phan tu dau mang (sau khi swap) 
void maxHeapify(int* &a, int n, int i) {
    int l = 2 * i + 1; // Left child index
    int r = 2 * i + 2; // Right child index
    int largest = i;

    if (l < n && a[l] > a[largest]) largest = l;
    if (r < n && a[r] > a[largest]) largest = r;
    if (largest != i) {
        swap(a[i], a[largest]);
        maxHeapify(a, n, largest);
    }
}
void buildMaxHeap(int* &a, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        maxHeapify(a, n, i);
    }
}
void heapSort(int* &a, int n) {
    buildMaxHeap(a, n);
    for (int i = n - 1; i > 0; i--) {
        swap(a[i], a[0]);
        maxHeapify(a, i, 0); // Use 'i' as the new size of the heap
    }
}

double compare(int *a, int n, int whatSort = 1){
    auto start = chrono::high_resolution_clock::now();

    if (whatSort == 1) quickSort(a, n);
    else if (whatSort == 2) heapSort(a, n);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    if (whatSort == 1) cout << "QuickSort: " << duration.count() << " giay.\n";
    else if (whatSort == 2) cout << "HeapSort: " << duration.count() << " giay.\n";
    return duration.count();
}


int main(){
    int const SIZE = 100000;
    int const NUM_ALGO = 2;
    int* randomArr = new int [SIZE];
    for (int i = 0; i < SIZE; i++) randomArr[i] = rand() % 100000 + 1;

    double* time = new double[NUM_ALGO + 1];
    for (int i = 1; i <= NUM_ALGO; i++){
        int* testArr = new int [SIZE];
        for (int i = 0; i < SIZE; i++) testArr[i] = randomArr[i];
        time[i] = compare(testArr, SIZE, i);
    }

    cout << "\n";
    if (time[1] <= time[2]) {
        cout << "The fastest algorithm: Quick Sort.\n"; 
        cout << "The slowest algorithm: Heap Sort.\n";
    } else {
        cout << "The fastest algorithm: Heap Sort.\n";
        cout << "The slowest algorithm: Quick Sort.\n";
    }
    
}