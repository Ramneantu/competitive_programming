#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

int bitRemoval(int x, int y) {
    int z = x;
    for(int i=0; i<32; ++i){
        if(((1<<i) & x) && ((1<<i) & y))
            z = (1<<i) ^ z;
    }
    return z;
}
   
int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; ++i) {
        int x, y;
        cin >> x >> y;
        cout << bitRemoval(x, y) << "\n";
    }
    return 0;
}

