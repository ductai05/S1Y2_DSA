#include <iostream>
using namespace std;

void inputArray(int* &arr , int n) {
    arr = new int [n];
    for (int i = 0; i < n; i++) cin >> arr[i];
}

void printArray(int* arr , int n) {
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << "\n";
}

int findMax(int* arr, int n) {
    int max = arr[0];
    for (int i = 0; i < n; i++) {
        if (max < arr[i]) max = arr[i];
    }
    return max;
}

int sumArray(int* arr , int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) sum += arr[i];
    return sum;
}

void concatArrays(int *a, int na, int *b, int nb, int* &res, int &nres ) {
     nres = na + nb;
     for (int i = 0; i < na; i++) res[i] = a[i];
     for (int i = 0; i < nb; i++) res[i + na] = b[i];
}

void findLongestAscendingSubarray(int *arr, int n, int* &res , int &nres) {
    res = new int [n];
    int* dp = new int [n]; 
    dp[0] = 1;
    int l = 0, r = 0;
    for (int i = 1; i < n; i++){
        if (arr[i] > arr[i - 1]) dp[i] = 1 + dp[i - 1];
        else dp[i] = 1;
    }
    int max = findMax(dp, n);
    nres = max;
    // printArray(dp, n);
    for (int i = 0; i < n; i++) if (dp[i] == max) {
        r = i; l = i - max + 1;
    }
    for (int i = l; i <= r; i++){
        res[i - l] = arr[i];
    }
}


int main() {
    int na; cin >> na;
    int *a; inputArray(a, na);
    int nb; cin >> nb;
    int *b; inputArray(b, nb);
    int *c; int nc;
    concatArrays(a, na, b, nb, c, nc);
    printArray(c, nc);
    cout << "Max(c) = " << findMax(c, nc) << "\n";
    cout << "Sum(c) = " << sumArray(c, nc) << "\n";
    int *l; int nl;
    findLongestAscendingSubarray(c, nc, l, nl);
    cout << "Longest Ascending Subarray of c:\n"; printArray(l, nl);
    delete []a; delete []b; delete []c; delete []l;
}
