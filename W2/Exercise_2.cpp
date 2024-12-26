#include <iostream>
using namespace std;

// Sort an integer array with even numbers in ascending order and odd numbers in descending order.
// Note that, positions of even and odd parts is no change.

void printArray(int* a, int n){
    for (int i = 0; i < n ; i++) cout << a[i] << " ";
    cout << "\n";
}

void ascendingInsertionSort(int* &a, int n){
    for (int i = 1; i < n; i++){
        int pos = i, x = a[i]; // lay phan tu a[i] de sap xep vao mang a[0], a[i - 1]
        while (pos > 0 && x < a[pos - 1]){
            a[pos] = a[pos - 1];
            pos -= 1;
        }
        a[pos] = x;
    }
}

void descendingInsertionSort(int* &a, int n){
    for (int i = 1; i < n; i++){
        int pos = i, x = a[i]; // lay phan tu a[i] de sap xep vao mang a[0], a[i - 1]
        while (pos > 0 && x > a[pos - 1]){
            a[pos] = a[pos - 1];
            pos -= 1;
        }
        a[pos] = x;
    }
}

void sortEvenOdd(int* &a, int n){
    int lenOdd = 0, lenEven = 0;
    int *mod2 = new int [n];
    for (int i = 0; i < n; i++){
        if (a[i] % 2 == 0) {
            lenEven += 1; mod2[i] = 0;
        } else {
            lenOdd += 1; mod2[i] = 1;
        }
    }

    int *odd = new int[lenOdd];
    int *even = new int[lenEven];
    int idOdd = 0, idEven = 0;
    for (int i = 0; i < n; i++){
        if (a[i] % 2 == 0) {
            even[idEven] = a[i]; idEven++;
        } else {
            odd[idOdd] = a[i]; idOdd++;
        }
    }

    ascendingInsertionSort(even, lenEven);
    descendingInsertionSort(odd, lenOdd);

    idOdd = 0, idEven = 0;
    for (int i = 0; i < n; i++){
        if (a[i] % 2 == 0) {
            a[i] = even[idEven]; idEven++;
        } else {
            a[i] = odd[idOdd]; idOdd++;
        }
    }
}

int main(){
    int n; cin >> n;
    int *a = new int[n];
    for (int i = 0; i < n; i++) cin >> a[i];
    
    sortEvenOdd(a, n);
    printArray(a, n);

    delete[] a;
    return 0;
}