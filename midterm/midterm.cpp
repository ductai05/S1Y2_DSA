#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
using namespace std;

void readFileIfStream(int &n, int &x, int* &a){
    ifstream inputFile("input_1.txt");
    string line, numstr;
    getline(inputFile, line);
    stringstream ss(line);
    getline(ss, numstr, ' ');
    n = stoi(numstr);
    getline(ss, numstr, ' ');
    x = stoi(numstr);

    int *b = new int [n];
    getline(inputFile, line);
    stringstream nss(line);
    for (int i = 0; i < n; i++){
        getline(nss, numstr, ' ');
        b[i] = stoi(numstr);
    }
    swap(a, b);
    inputFile.close();
}

void readFile(int &n, int &x, int* &a){
    freopen("input_1.txt", "r", stdin);
    cin >> n >> x;
    int *b = new int [n];
    for (int i = 0; i < n; i++) cin >> b[i];
    swap(a, b);
}

int binarySearch(int* a, int l, int r, int x){
    while(l <= r){
        int mid = l + (r - l) / 2;
        if (a[mid] == x) return mid;
        if (a[mid] > x) r = mid - 1;
        else l = mid + 1;
    }
    return -1;
}
int main(){
    int* a; int n, x;
    readFile(n, x, a);
    // cout << n << " " << x << "\n";
    // for (int i = 0; i < n; i++) cout << a[i] << " ";
    // cout << "\n";

    int ans = -1;
    int ans_ai = 0, ans_aj = 0;
    for (int i = 0; i < n; i++){
        int aj = x - a[i];
        binarySearch(a, i + 1, n - 1, aj);
        if (aj != -1){
            if (a[i] * aj > ans){
                ans = max(ans, a[i] * aj);
                ans_ai = a[i];
                ans_aj = aj;
            }
        }
    }
    freopen("output_1.txt", "w", stdout);
    cout << ans_ai << " " << ans_aj << "\n";
}