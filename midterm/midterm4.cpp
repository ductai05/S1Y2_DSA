#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
using namespace std;

void solve(){
    long long a, b; cin >> a >> b;
    long long ans = min(min(a, b), (a + b)/4);
    cout << ans << "\n";
}

int main(){
    int t = 1; cin >> t;
    while(t--){
        solve();
    }
}