#include <iostream>
#include <string>
using namespace std;

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

int linearSearch(int *a, int n, int x){
    for (int i = 0; i < n; i++){
        if (a[i] == x) return i;
    }
    return -1;
}

int sentinelSearch(int *a, int n, int x){
    int last = a[n - 1];

    a[n - 1] = x;
    int i = 0;
    while (a[i] != x){
        i++;
    }
    a[n - 1] = last;

    if ((i < n - 1) || (a[n - 1] == x))
        return i;
    else
        return -1;
}

int binSearch(int *a, int n, int x, int left, int right){
    if (left > right) return -1;
    int mid = (left + right) / 2;
    if (a[mid] == x) return mid;
    else {
        if (a[mid] > x) return binSearch(a, n, x, left, mid - 1);
        else return binSearch(a, n, x, mid + 1, right);
    }
}

int binarySearch(int* a, int n, int x){
    return binSearch(a, n, x, 0, n - 1);
}

int main(int argc, char* argv[])
{
    if (argc < 2) return 1;
    
    int searchAlgorithm = atoi(argv[1]);
    int x = atoi(argv[2]);
    string inputFile = (argc > 3) ? argv[3] : "input.txt";
    string outputFile = (argc > 4) ? argv[4] : "output.txt";

    freopen(inputFile.c_str(), "r", stdin);
    freopen(outputFile.c_str(), "w", stdout);
    
    int n; cin >> n;
    int* a = new int[n];
    for (int i = 0; i < n; i++) cin >> a[i];

    int result;
    
    switch(searchAlgorithm) {
        case 1: result = linearSearch(a, n, x); break;
        case 2: result = sentinelSearch(a, n, x); break;
        case 3: {
            quickSort(a, n); // Sort array before searching
            result = binarySearch(a, n, x); break;
        }
        default: result = -1;
    }
    
    cout << result;
    delete[] a;
    return 0;
}