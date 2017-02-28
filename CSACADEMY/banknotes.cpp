#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int banknotes(int A, int B, int S, int N) {
    for(int a = N; a >= 0; --a){
        if(S - a*A - N*B + a*B == 0)
            return a;
    }
    return -1;
}

int main() {
    int A, B, S, N;
    cin >> A >> B >> S >> N;
    cout << banknotes(A, B, S, N) << "\n";
    return 0;
}

