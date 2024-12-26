#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;

// Implement sort algorithms include insertion sort, selection sort and interchange sort for
// integer array with random values.
// Compare the system time on a random array of size 10000 or more. Note that all algorithms
// should use the same data to ensure fairness when comparing.

void printArray(int* a, int n){
    for (int i = 0; i < n ; i++) cout << a[i] << " ";
    cout << "\n";
}

// insertionSort sap xep theo nguyen ly xep bai tay
void insertionSort(int* &a, int n){
    for (int i = 1; i < n; i++){
        int pos = i, x = a[i]; // lay phan tu a[i] de sap xep vao mang a[0], a[i - 1]
        while (pos > 0 && x < a[pos - 1]){
            a[pos] = a[pos - 1];
            pos -= 1;
        }
        a[pos] = x;
    }
}

// selectionSort tim phan tu nho nhat trong mang (duyet het), day len dau
void selectionSort(int* &a, int n){
    for (int i = 0; i < n; i++){
        int pos = i, now = a[i];
        for (int j = i; j < n; j++){
            if (now >= a[j]) {
                pos = j; now = a[j];
            }
        }
        int temp = a[i]; // swap(a[i], a[pos]);
        a[i] = a[pos];
        a[pos] = temp;
    }
}

// interchangeSort tim va ngay lap tuc day phan tu nho hon len dau
void interchangeSort(int* &a, int n){
    for (int i = 0; i < n; i++){
        for (int j = i; j < n; j++){
            if (a[j] < a[i]){
                int temp = a[i]; //swap(a[i], a[j]);
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}

void compare(int *a, int n, int whatSort = 3){
    if (whatSort == 1) {
        auto start = chrono::high_resolution_clock::now();
        insertionSort(a, n); 
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;
        cout << "InsertionSort: " << duration.count() << " giay.\n";
    } else if (whatSort == 2) {
        auto start = chrono::high_resolution_clock::now();
        selectionSort(a, n); 
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;
        cout << "SelectionSort: " << duration.count() << " giay.\n";
    } else {
        auto start = chrono::high_resolution_clock::now();
        interchangeSort(a, n); 
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;
        cout << "InsertionSort: " << duration.count() << " giay.\n";
    }
}

int main(){
    // int n; cin >> n;
    // int *a = new int[n];
    // for (int i = 0; i < n; i++) cin >> a[i];
    
    int const SIZE = 100000;
    int randomArr[SIZE];
    for (int i = 0; i < SIZE; i++) randomArr[i] = rand() % 100000 + 1;
    compare(randomArr, SIZE, 1);
    compare(randomArr, SIZE, 2);
    compare(randomArr, SIZE, 3);
    
    // delete[] a;
    return 0;
}