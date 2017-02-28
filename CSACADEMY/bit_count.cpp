#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

int bitcount(int x) {
    int cnt=0;
    while(x){
        x = (x-1) & x;
        cnt++;
    }
    return cnt;
}
int main() {
    int x;
    cin >> x;
    cout << bitcount(x) << "\n";
    return 0;
}

