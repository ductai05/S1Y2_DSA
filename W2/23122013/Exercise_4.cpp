#include<iostream>
using namespace std;

void printMatrix(int **a, int aRows, int aCols){
    for (int i = 0; i < aRows; i++){
        for (int j = 0; j < aCols; j++){
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }
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

void sortMatrixToList(int **a, int aRows, int aCols, int* &b){
    int idb = 0;
    for (int i = 0; i < aRows; i++){
        for (int j = 0; j < aCols; j++){
            b[idb] = a[i][j];
            idb++;
        }
    }
    insertionSort(b, aRows * aCols);
}

void spiral(int **a, int aRows, int aCols, int *b){
    int stRow, stCol; stRow = stCol = 0;
    int enRow, enCol; enRow = aRows - 1; enCol = aCols - 1;
    int idb = 0;
    while (stRow <= enRow && stCol <= enCol){
        for (int i = stCol; i <= enCol; i++){
            a[stRow][i] = b[idb]; idb++; 
        }
        stRow++;
        for (int i = stRow; i <= enRow; i++){
            a[i][enCol] = b[idb]; idb++; 
        }
        enCol--;
        if (!(stRow <= enRow && stCol <= enCol)) break;
        for (int i = enCol; i >= stCol; i--){
            a[enRow][i] = b[idb]; idb++; 
        }
        enRow--;
        for (int i = enRow; i >= stRow; i--){
            a[i][stCol] = b[idb]; idb++; 
        }
        stCol++;
    }
}

int main(){
    int aRows = 5, aCols = 5;
    cout << "Input aRows, aCols: ";
    cin >> aRows >> aCols;
    cout << "Input matrix:\n";
    int **a = new int *[aRows];
    int *b = new int [aRows * aCols];
    for (int i = 0; i < aRows; i++){
        a[i] = new int [aCols];
    }
    for (int i = 0; i < aRows; i++){
        for (int j = 0; j < aCols; j++){
            cin >> a[i][j];
        }
    }
    // printMatrix(a, aRows, aCols);
    sortMatrixToList(a, aRows, aCols, b);
    cout << "\n";
    spiral(a, aRows, aCols, b);
    printMatrix(a, aRows, aCols);
}