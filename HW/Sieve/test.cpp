#include <iostream> 

using namespace std;

int main() {
    int count = 0;
    int n = 10;
    for (int i = 1; i * i <= n; i++) {
        count++;    
    }    
    cout << count;
}

