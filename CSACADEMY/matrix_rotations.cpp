#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <map>
#include <utility>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef pair<int, int> ii;

int main() {
    int N;
    cin >> N;
    vector<vector<int> > A(N,vector<int>(N)), B(N,vector<int>(N,0));
    for(int i=0; i<N; ++i)
        for(int j=0; j<N; ++j)
            cin >> A[i][j];
            
    for(int i=0; i<N; ++i)
        for(int j=0; j<N; ++j){
            int e = 0;
            // 90°
            if(A[N-j-1][i])
                e = 1;
            // 180°
            if(A[N-i-1][N-j-1])
                e = 1;
            // 270°
            if(A[j][N-i-1])
                e = 1;
            if(A[i][j])
                e = 1;
            B[i][j] = e;
            
        }
    
    for(int i=0; i<N; ++i){
        for(int j=0; j<N; ++j)
            cout << B[i][j] << " ";
        cout << "\n";
    }
    
}

