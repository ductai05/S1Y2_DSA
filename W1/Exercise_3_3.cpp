#include <iostream>
using namespace std;

int fibonacci(int i) {
    if (i == 0) return 0;
    else if (i == 1) return 1;
    return fibonacci(i - 1) + fibonacci(i - 2);
}

int main() {
    cout << fibonacci(5) << "\n";
}
