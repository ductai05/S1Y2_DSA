#include <iostream>
#include <vector>
using namespace std;

void partition(vector<int> &v, int l, int r, int &p){
    int mid = l + (r - l) / 2;
    if (v[l] > v[mid]) swap(v[l], v[mid]);
    if (v[l] > v[r]) swap(v[l], v[r]);
    if (v[r] > v[mid]) swap(v[r], v[mid]); // l < r < mid

    int pivot = v[r];
    int i = l - 1;
    for (int j = l; j < r; j++){
        if (v[j] < pivot){
            i++;
            swap(v[i], v[j]);
        }
    }
    swap(v[i + 1], v[r]);
    p = i + 1;
}

void quickSortRecursion(vector<int> &v, int l, int r){
    if (l <= r){
        int p;
        partition(v, l, r, p);
        quickSortRecursion(v, l, p - 1);
        quickSortRecursion(v, p + 1, r);
    }
}

void sortVector(vector<int> &v){
    quickSortRecursion(v, 0, v.size() - 1);
}

void sortMatrix(int** &a, int m, int n){
    // first row :: sort
    for (int i = 0; i < n; i++){ 
        vector<int> v;
        for (int j = 0; j < m; j++){
            if (j < m && i + j < n){
                v.push_back(a[j][i + j]);
            } else break;
        }
        sortVector(v);

        int k = 0;
        for (int j = 0; j < m; j++){
            if (j < m && i + j < n){
                a[j][i + j] = v[k];
                k++;
            } 
        }
    }

    // first col :: sort
    for (int i = 1; i < m; i++){ // start row
        vector<int> v;
        for (int j = 0; j < n; j++){
            if (i + j < m && j < n){
                v.push_back(a[i + j][j]);
            }
        }
        sortVector(v);

        int k = 0;
        for (int j = 0; j < n; j++){
            if (i + j < m && j < n){
                a[i + j][j] = v[k];
                k++;
            }
        }
    }
}

int main(){
    freopen("input_2.txt", "r", stdin);
    int m, n; cin >> m >> n;
    int **a = new int* [m];
    for (int i = 0; i < m; i++){
        a[i] = new int [n];
        for (int j = 0; j < n; j++) cin >> a[i][j];
    }
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            cout << a[i][j] << " ";
        } cout << "\n";
    }
    sortMatrix(a, m, n);

    cout << "\n";
    freopen("output_2.txt", "w", stdout);
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            cout << a[i][j] << " ";
        } cout << "\n";
    }
}